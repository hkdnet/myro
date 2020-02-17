let mePath = "/1/users/me";
let baseUrl = "https://api.nature.global";

type getMeResponse = {
  id: string,
  nickname: string,
};

let getRequest = (token: string, path: string) => {
  let url = {j|$baseUrl$path|j};

  Js.Promise.(
    Fetch.fetchWithInit(
      url,
      Fetch.RequestInit.make(
        ~method_=Fetch.Get,
        ~headers=
          Fetch.HeadersInit.make({"Authorization": {j|Bearer $token|j}}),
        (),
      ),
    )
    |> then_(Fetch.Response.json)
  );
};

let getMe = (token: string) => {
  getRequest(token, mePath);
};

let devicesPath = "/1/devices";
let getDevices = (token: string) => {
  getRequest(token, devicesPath);
};
//   let payload = Js.Dict.empty();
// ~body=
//   Fetch.BodyInit.make(Js.Json.stringify(Js.Json.object_(payload))),

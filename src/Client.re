let mePath = "/1/users/me";
let baseUrl = "https://api.nature.global";

type getMeResponse = {
  id: string,
  nickname: string,
};

let getRequest = (token: string, path: string) => {
  let url = {j|$baseUrl$path|j};

  Fetch.fetchWithInit(
    url,
    Fetch.RequestInit.make(
      ~method_=Fetch.Get,
      ~headers=Fetch.HeadersInit.make({"Authorization": {j|Bearer $token|j}}),
      (),
    ),
  )
  |> Js.Promise.then_(Fetch.Response.json);
};

let getMe = (token: string) => {
  getRequest(token, mePath);
};

type sensorValue = {
  value: float,
  createdAt: Js.Date.t,
};
type newestEvents = {
  temperature: sensorValue,
  humidity: sensorValue,
  illumination: sensorValue,
  movement: sensorValue,
};
type device = {
  name: string,
  temperatureOffset: float,
  humidityOffset: float,
  newestEvents,
};
let decodeSensorValue = json => {
  {
    value: json |> Json.Decode.field("val", Json.Decode.float),
    createdAt: json |> Json.Decode.field("created_at", Json.Decode.date),
  };
};

let decodeNewestEvent = json => {
  Json.Decode.{
    temperature: json |> field("te", decodeSensorValue),
    humidity: json |> field("hu", decodeSensorValue),
    illumination: json |> field("il", decodeSensorValue),
    movement: json |> field("mo", decodeSensorValue),
  };
};
let decodeDevice = json => {
  {
    name: json |> Json.Decode.field("name", Json.Decode.string),
    temperatureOffset:
      json |> Json.Decode.field("temperature_offset", Json.Decode.float),
    humidityOffset:
      json |> Json.Decode.field("humidity_offset", Json.Decode.float),
    newestEvents:
      json |> Json.Decode.field("newest_events", decodeNewestEvent),
  };
};
let decodeDevices = Json.Decode.array(decodeDevice);

let devicesPath = "/1/devices";
let getDevices = (token: string) => {
  getRequest(token, devicesPath)
  |> Js.Promise.then_(body => Js.Promise.resolve(decodeDevices(body)));
};

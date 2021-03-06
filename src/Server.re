open Express;

let createMetrics = devices => {
  let f = (device: Client.device) => {
    let name = device.name;
    let ev = device.newestEvents;
    Js.Console.log(ev);
    let metrics = Js.Dict.empty();
    Js.Dict.set(
      metrics,
      {j|nature_temperature{device_name="$name"}|j},
      Js.Json.number(ev.temperature.value +. device.temperatureOffset),
    );
    Js.Dict.set(
      metrics,
      {j|nature_humidity{device_name="$name"}|j},
      Js.Json.number(ev.humidity.value +. device.humidityOffset),
    );
    Js.Dict.set(
      metrics,
      {j|nature_illumination{device_name="$name"}|j},
      Js.Json.number(ev.illumination.value),
    );
    Js.Dict.set(
      metrics,
      {j|nature_movement{device_name="$name"}|j},
      Js.Json.number(ev.movement.value),
    );
    metrics;
  };
  Array.map(f, devices);
};
let start = (token, port) => {
  let app = express();

  // remove X-Powered-By header
  App.disable(app, ~name="x-powered-by");

  App.get(app, ~path="/metrics") @@
  PromiseMiddleware.from((_next, _req, res) => {
    Js.Console.log("request received");
    Client.getDevices(token)
    |> Js.Promise.then_(devices => {
         let metrics = createMetrics(devices);
         let body =
           Array.fold_left(
             (s, metrics) => {
               let lines =
                 Js.Dict.entries(metrics)
                 |> Array.map(((k, v)) => {j|$k $v|j});
               let b = String.concat("\n", Array.to_list(lines));
               String.concat("\n", [b, s]);
             },
             "",
             metrics,
           );

         Js.Promise.resolve(Response.sendString(body, res));
       });
  });

  App.listen(app, ~port, ());
};

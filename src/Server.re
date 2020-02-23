open Express;

let createMetrics = devices => {
  let f = (device: Client.device) => {
    let name = device.name;
    let ev = device.newestEvents;
    let metrics = Js.Dict.empty();
    Js.Dict.set(
      metrics,
      {j|nature-temperature{device_name=$name}|j},
      Js.Json.number(ev.temperature.val_ +. device.temperatureOffset),
    );
    Js.Dict.set(
      metrics,
      {j|nature-humidity{device_name=$name}|j},
      Js.Json.number(ev.humidity.val_ +. device.humidityOffset),
    );
    Js.Dict.set(
      metrics,
      {j|nature-illumination{device_name=$name}|j},
      Js.Json.number(ev.illumination.val_),
    );
    Js.Dict.set(
      metrics,
      {j|nature-movement{device_name=$name}|j},
      Js.Json.number(ev.movement.val_),
    );
    metrics;
  };
  Array.map(f, devices);
};
let start = (token, port) => {
  let app = express();

  // remove X-Powered-By header
  App.disable(app, ~name="x-powered-by");

  // nature-$device-humidity
  // nature-$device-temperature
  // nature-$device-humidity
  // nature-$device-humidity
  App.get(app, ~path="/") @@
  PromiseMiddleware.from((_next, _req, res) => {
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
               String.concat("\n", [s, b]);
             },
             "",
             metrics,
           );

         Js.Promise.resolve(Response.sendString(body, res));
       });
  });

  App.listen(app, ~port, ());
};

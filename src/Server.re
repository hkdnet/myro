open Express;

let start = (token, port) => {
  let app = express();

  // remove X-Powered-By header
  App.disable(app, ~name="x-powered-by");

  App.get(app, ~path="/") @@
  PromiseMiddleware.from((_next, _req, res) => {
    Client.getDevices(token)
    |> Js.Promise.then_(e => Js.Promise.resolve(Response.sendJson(e, res)))
  });

  App.listen(app, ~port, ());
};

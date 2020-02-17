[%raw "require('isomorphic-fetch')"];

let () = Js.log("Hello, BuckleScript");
let abort = message => {
  Js.Console.error(message);
  exit(1);
};
let main = token => {
  Client.getDevices(token)
  |> Js.Promise.then_(e => {
       Js.Console.log(e);
       Js.Promise.resolve();
     });
};
let tokenOp = Js.Nullable.toOption(Env.natureToken);
switch (tokenOp) {
| None => abort("No token")
| Some(token) => main(token)
};

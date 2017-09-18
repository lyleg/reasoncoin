open Express;

let app = express ();

let makeSuccessJson () => {
  let json = Js.Dict.empty ();
  Js.Dict.set json "success" (Js.Json.boolean Js.true_);
  Js.Json.object_ json
};



App.post app path::"/txion" @@
Middleware.from (
  fun req res next =>
    switch (Request.baseUrl req) {
    | "" => Response.sendJson res (makeSuccessJson ())
    | _ => next Next.route
    }
);

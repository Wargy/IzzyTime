/**
 * Created by marinaefimova on 25.04.14.
 */

var db=require('./database');

module.exports = function (app) {
    app.post('/sync', function (req, res) {
//        if (req.isAuthenticated()) {
//            //res.redirect('/');
//            console.log("synchronization handler");
//            return;
//        }
console.log(req.contentType);
        if (req.is('*/json')) {
    //        console.log(req.body);
            var body = (req.body);

            for (i = 0; i < body['TimeLine'].length; i++) {
              //  console.log("body.[i]=\n");
console.log((body['TimeLine'][i]));
            if ((body['TimeLine'][i]).saved == 0) {
                console.log("FALSE");
                db.update(body['TimeLine'][i]);
            }
        }
            res.writeHead(200,{'Content-Type':'application/json'});
          //  res.end(JSON.stringify(jsonObject));
            res.end();

        }

    });
};
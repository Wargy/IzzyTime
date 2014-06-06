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
        if (req.is('*/json')) {
            var body = JSON.parse(req.body);

            for (i = 0; i < body['TimeLine'].length; i++) {

            if (body['TimeLine'][i].saved == 0) {
                db.update(body[i]);
            }
        }
            return;
        }

    });
}
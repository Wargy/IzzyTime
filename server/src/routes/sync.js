/**
 * Created by marinaefimova on 25.04.14.
 */

var db = require('./database');

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
            //    console.log(body);
            var len = body['TimeLine'].length;
            for (i = 0; i < len; i++) {
                if ((body['TimeLine'][i]).saved == 0) {
                    db.update(body['TimeLine'][i], 'db');
                }
            }
            db.getCount('db', function (err, result) {
                if (result > len) {
                    console.log(">0");
                    var json = '{TimeLine: [';
                    db.getAllRecords('db', function (err, result) {
                        for (var i = 0; i < result.length; i++) {

                            json += ('{ DateStart: ' + result[i].DateStart);
                            json += (', DateEnd: ' + result[i].DateEnd);
                            json += (', TimeStart: ' + result[i].TimeStart);
                            json += (', TimeEnd: ' + result[i].TimeEnd);
                            json += (', Title: ' + result[i].Title);
                            json += (', Text: ' + result[i].Text + ' }');
                            if (i + 1 < result.length) {
                                json += ' ,\n';
                            } else {
                                json += ']}';
                            }
                        }
                        res.contentType('application/json');
                        res.end(JSON.stringify(json));
                    });
                } else {
                    res.writeHead(200);
                    res.end();
                }
            });
        }
    });
};
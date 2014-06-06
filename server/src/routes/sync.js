/**
 * Created by marinaefimova on 25.04.14.
 */
//var pool = require('pool');
var jsonObject={
    Name: 'Marina',
    Age: 21,
    Detail: 'This is example'
}
var sql;
var db=require('./database');

module.exports = function (app) {
    app.post('/sync', function (req, res) {

//        if (req.isAuthenticated()) {
//            //res.redirect('/');
//            console.log("synchronization handler");
//            return;
//        }
        if (req.is('*/json')) {
            var body = req.body;

//            console.log(body);
//            sql='update test set name=marina value=efimova;';
//pool.query(sql,function(err, rows, fields) {
//                if (err) throw err;
//
//               // console.log('The solution is: ', rows[0].solution);});
//});
            // var record=JSON.parse(body);
            //   var json=JSON.stringify(body);
            for (i = 0; i < body.length; i++) {
               // console.log(body[i]);
            if (body[i].saved == 0) {
                db.update(body[i]);
            }
        }
            return;
        }



//        res.render('auth', {
//            error: req.flash('error')
//        });
    });
}
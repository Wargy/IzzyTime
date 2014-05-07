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
            var body=req.body;
            console.log(body);
//            sql='update test set name=marina value=efimova;';
//pool.query(sql,function(err, rows, fields) {
//                if (err) throw err;
//
//               // console.log('The solution is: ', rows[0].solution);});
//});
           // var record=JSON.parse(body);
         //   var json=JSON.stringify(body);
db.update(body);
            res.writeHead(200,{'Content-Type':'application/json'});
            res.end(JSON.stringify(jsonObject));
            return;
        }



//        res.render('auth', {
//            error: req.flash('error')
//        });
    });
}
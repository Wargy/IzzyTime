/**
 * Created by marinaefimova on 25.04.14.
 */
var mysql = require('mysql');
var pool;
//config.argv()
//    .env()
//    .file({ file: 'config.json' });
pool=mysql.createPool({
        host: 'localhost',
        user: 'root',
        database: 'test2'
    }
);
var query;
//var record={
//    DataTimeUpdate:"",
//    DataTimeStart:"",
//    DataTimeEnd:"",
//    Title:"",
//    Text:"",
//    Priority:"",
//    Reminder:"",
//    Color:"",
//    WeekMask:""
//}
exports.getConnection = function(){
    return pool.getConnection();
}

exports.update=function(record){
    pool.getConnection(function(err, connection){
        if (err) throw err;
var query='INSERT INTO db (DateTimeUpdate, DateStart, DateEnd, Title, Text, Priority, Reminder, Color, WeekMask) ' +
    'VALUES (\''+record.DateTimeUpdate+'\',\''+record.DateStart+'\',\''+record.DateEnd+'\',\''+record.Title+'\',\''+record.Text+'\',\''+
    record.Priority+'\',\''+record.Reminder+'\',\''+record.Color+'\',\''+record.WeekMask+
    '\')ON DUPLICATE KEY UPDATE DateTimeUpdate=\''+record.DateTimeUpdate+'\', DateStart=\''+record.DateStart+
    '\',DateEnd=\''+record.DateEnd+'\',Title=\''+record.Title+'\',Text=\''+record.Text+'\',Priority=\''+record.Priority+
    '\',Reminder=\''+record.Reminder+'\',Color=\''+record.Color+'\',WeekMask=\''+record.WeekMask+'\';';
console.log(query);
            connection.query(query, function (err, rows) {
            //connection.release();
            if (err) {
                throw err;
            } else {
                console.log(rows);

                console.log('Query');
            }
            connection.release();
        });
    });
}

exports.select=function(date_start,date_end){

}

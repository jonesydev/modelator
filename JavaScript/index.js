const express = require("express");
const app = express();
const bodyParser = require("body-parser");
const port = 3000;

const execFile = require('child_process').execFile
const program = "../../JDSstatCalc/Debug/JDSstatCalc";

app.use(express.static("public"));
app.use(bodyParser.text());
app.use(bodyParser.json());

app.use(bodyParser.urlencoded({
  extended: true
}));

//var types = [
//  {
//    title: "stats_calculator",
//    description: "A simple statistics calulator."
//  }
//];

//types.forEach(function (type) {
//  app.use("/" + type.title, require("./routes/" + type.title));
//});
//
//app.get("/", function (req, res) {
//  res.render("index", {routes: types});
//});

app.post("/", (req, res) => {
  //var data_set = req.body.data_values;
  var data_set = req.body;
  var results = "";
  
  console.log(data_set);
  
  var child = execFile(program, [data_set], (error, stdout, stderr) => {
    if (error) {
      throw error;
    }
    
    results = stdout.split("\n");    
    console.log(JSON.stringify(results));    //DEBUG ONLY 
    res.header("Access-Control-Allow-Origin", "*");
    res.send(JSON.stringify(results));     
  });  
});

app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}/`);
});


/**
 * 
 */
//var Modelator = ( function() {

  //import { reactive } from "vue";
  
  var data_values = [];
  var datasets = [];
  var url = "http://localhost:3000";
  
  var input_enter = document.getElementById("data_value_input");
  
  input_enter.addEventListener("keydown", event => {
    if (event.code == "Enter" || event.keyCode === 13) {      
      document.getElementById("enter_data_value").click();
    }
  });
  
  function init_page() {
    document.getElementById("data_value_input").focus();
  }
  
  function add_data_to_array(dv) {
    data_values.push(dv);
    display_current_set();
  }
  
  function display_current_set() {    
    document.getElementById("dataset").innerHTML = "<strong>Current Data Set:</strong> " + data_values;
    clear_data_value_input();
  }
  
  function clear_current_set() {
    data_values.splice(0, data_values.length);
    display_current_set();
  }
  
  function clear_data_value_input() {
    document.getElementById("data_value_input").value = "";
    document.getElementById("data_value_input").focus();
  }
  
  function display_datasets() {
    var datasets_html_string = "";
    var set_number = 0;
    
    for (var i = 0; i < datasets.length; i++) {
      set_number = i + 1;
      datasets_html_string += "<br><label id='dataset_" + set_number + "'><strong>Data Set " + set_number + ":</strong> " + datasets[i] + "</label><br>";
    }
    
    document.getElementById("datasets_input").innerHTML = datasets_html_string;
    clear_current_set();
    display_current_set();
    clear_data_value_input();
  }  
  
  function clear_all() {    
    location.reload();
  }
  
  function backspace_data_array() {
    data_values.pop();
    display_current_set();
  }
  
  function calculate() {
    send_node_request();
  }
  
  function add_dataset() {
    ds = data_values.map((x) => x);
    datasets.push(ds);
    display_datasets();
  }
  
  function send_node_request() {
    fetch(url, {
      method: "POST",
      body: data_values
    })
      .then(
          function(response) {
            if (response.status !== 200) {
              console.log("We have a problem. Status code: " + response.status);
              return;
            }
            else {
              response.json().then(function(data) {                
                handle_node_response(JSON.parse(data));
              })
            }
          })
      .catch(function(err) {
        console.log("Fetch Error :-S", err);
      });
  }
  
    
  function handle_node_response(res) {
    //document.getElementById("frequency_table").tBodies[0].innerHTML = "";
    generate_frequency_table(res);
    generate_innerHTML(res);
    generate_charts(res);
    //generate_console_log(res);
    document.getElementById("clear_all").focus();
  }
  
  function generate_multiple_dataset_output() {
    var datasets_output_html_string = "";
    var set_number = 0;
    
//    for (var i = 0; i < datasets.length; i ++) {
//      set_number = i + 1;
//      
//      datasets_output_html_string += "<br><br>" +=        
//        "<div class='row'>" +=
//          "<div class='column'>" +=
//            "<label id='minimum'><strong>Minimum:</strong></label>" +=      
//          "</div>" +=
//          "<div class='column'>"
//            "<label id='maximum'><strong>Maximum:</strong></label>"          
//          "</div>"
//          "<div class='column'>" +=
//            "<label id='mean'><strong>Mean:</strong></label>" +=          
//          "</div>" +=        
//        "</div>" +=            
//        "<div class='row'>" +=
//           "<div class='column'>" +=
//             "<label id'count'><strong>Count:</strong></label>" +=
//           "</div>" +=
//           "<div class='column'>" +=
//             "<label id='sum'><strong>Sum:</strong></label>" +=        
//           "</div>" +=  
//           "<div class='column'>" +=
//             "<label id='standard_deviation'><strong>Standard deviation:</strong></label>" +=        
//           "</div>" +=        
//         "</div>";
//    }
  }
  
  function generate_frequency_table(res) {
    var freq_table = document.getElementById("frequency_table");
    //var freq_table_body = document.getElementById("frequency_table").tBodies[0];
    var freq_table_body = document.createElement("tbody");   
            
    var number_of_rows = res.data_values.length;    
    
    for (var i = 0; i < number_of_rows; i++) {
      var row = document.createElement("tr");
      
      var cell_data = document.createElement("td");
      var cell_text_data = document.createTextNode(res.data_values[i]);
      cell_data.appendChild(cell_text_data);
      row.appendChild(cell_data);
      
      var cell_freq = document.createElement("td");
      var cell_text_freq = document.createTextNode(res.frequencies[i].toFixed(0));
      cell_freq.appendChild(cell_text_freq);
      row.appendChild(cell_freq);
      
      var cell_rel_freq = document.createElement("td");
      var cell_text_rel_freq = document.createTextNode(res.relative_frequencies[i].toFixed(4));
      cell_rel_freq.appendChild(cell_text_rel_freq);
      row.appendChild(cell_rel_freq);
      
      var cell_cum_rel_freq = document.createElement("td");
      var cell_text_cum_rel_freq = document.createTextNode(res.cumulative_relative_frequencies[i].toFixed(4));
      cell_cum_rel_freq.appendChild(cell_text_cum_rel_freq);
      row.appendChild(cell_cum_rel_freq);
      
      var cell_zscore = document.createElement("td");
      var cell_text_zscore = document.createTextNode(res.z_scores[i].toFixed(4));
      cell_zscore.appendChild(cell_text_zscore);
      row.appendChild(cell_zscore); 
      
      freq_table_body.appendChild(row);
    }
    
    freq_table.appendChild(freq_table_body);
  }
  
  function generate_innerHTML(res) {
    document.getElementById("minimum").innerHTML = "<strong>Minimum:</strong> " + res.minimum.toPrecision(4);
    document.getElementById("maximum").innerHTML = "<strong>Maximum:</strong> " + res.maximum.toFixed(4);
    document.getElementById("mean").innerHTML = "<strong>Mean:</strong> " + res.mean.toFixed(4);    
    
    document.getElementById("count").innerHTML = "<strong>Count:</strong> " + res.count.toFixed(4);
    document.getElementById("sum").innerHTML = "<strong>Sum:</strong> " + res.sum.toFixed(4);
    document.getElementById("standard_deviation").innerHTML = "<strong>Standard Deviation:</strong> " + res.standard_deviation.toFixed(4);
        
    document.getElementById("range").innerHTML = "<strong>Range:</strong> " + res.range.toFixed(4);
    document.getElementById("variance").innerHTML = "<strong>Variance:</strong> " + res.variance.toFixed(4);
    document.getElementById("mode").innerHTML = "<strong>Mode:</strong> " + res.mode;
    
    document.getElementById("percentile_25").innerHTML = "<strong>25<sup>th</sup> Percentile:</strong> " + res.percentile_25.toFixed(4);
    document.getElementById("median").innerHTML = "<strong>Median:</strong> " + res.median.toFixed(4);
    document.getElementById("percentile_75").innerHTML = "<strong>75<sup>th</sup> Percentile:</strong> " + res.percentile_75.toFixed(4);
    document.getElementById("iqr").innerHTML = "<strong>IQR:</strong> " + res.iqr.toFixed(4);
    
    document.getElementById("percentile_10").innerHTML = "<strong>10<sup>th</sup> Percentile:</strong> " + res.percentile_10.toFixed(4);
    document.getElementById("percentile_20").innerHTML = "<strong>20<sup>th</sup> Percentile:</strong> " + res.percentile_20.toFixed(4);
    document.getElementById("percentile_30").innerHTML = "<strong>30<sup>th</sup> Percentile:</strong> " + res.percentile_30.toFixed(4);
    document.getElementById("percentile_40").innerHTML = "<strong>40<sup>th</sup> Percentile:</strong> " + res.percentile_40.toFixed(4);
    
    document.getElementById("percentile_60").innerHTML = "<strong>60<sup>th</sup> Percentile:</strong> " + res.percentile_60.toFixed(4);
    document.getElementById("percentile_70").innerHTML = "<strong>70<sup>th</sup> Percentile:</strong> " + res.percentile_70.toFixed(4);
    document.getElementById("percentile_80").innerHTML = "<strong>80<sup>th</sup> Percentile:</strong> " + res.percentile_80.toFixed(4);
    document.getElementById("percentile_90").innerHTML = "<strong>90<sup>th</sup> Percentile:</strong> " + res.percentile_90.toFixed(4);       
  }
  
  function generate_console_log(res) {
    console.log("Data: " + res.data_values);
    console.log("Frequency: " + res.frequencies);
    console.log("Relative Frequencies: " + res.relative_frequencies);
    console.log("Cumulative Relative Frequencies: " + res.cumulative_relative_frequencies);
    console.log("Minimum: " + res.minimum);
    console.log("Maximum: " + res.maximum);
    console.log("Mean: " + res.mean);
    console.log("Median: " + res.median);
    console.log("Standard Deviation: " + res.standard_deviation);
    console.log("Mode: " + res.mode);
    console.log("Percentiles: ");
    console.log("25th: " + res.percentile_25);
    console.log("75th: " + res.percentile_75);    
    console.log("10th: " + res.percentile_10);
    console.log("20th: " + res.percentile_20);
    console.log("30th: " + res.percentile_30);
    console.log("40th: " + res.percentile_40);
    console.log("60th: " + res.percentile_60);
    console.log("70th: " + res.percentile_70);
    console.log("80th: " + res.percentile_80);
    console.log("90th: " + res.percentile_90);
    console.log("IQR: " + res.iqr);
    console.log("Z-Scores: " + res.z_scores);   
  }
  
  
  function generate_chart_box(data, res) {
    var svg_box = d3.select("#svg_box");
    var margin = 200;
    var width = svg_box.attr("width") - margin;
    var height = svg_box.attr("height") - margin;
    var q1 = res.percentile_25;
    var median = res.median;
    var q3 = res.percentile_75;
    var iqr = res.iqr;
    var min = res.minimum;
    var max = res.maximum;
    var center = 100;
    var height_box = 50;
   
    var xScale = d3.scaleBand().range([0, width]).padding(1);
    var yScale = d3.scaleLinear().range([height, 0]);
    var g = svg_box.append("g")
               .attr("transform", "translate(" + 100 + "," + 100 + ")");
    
    xScale.domain(data.map(function(d) { return d.value; }));
    yScale.domain([0, height]);
    //yScale.domain([0, d3.max(data, function(d) { return d.frequency })]);   
    
    g.append("g")
    .attr("transform", "translate(0," + height + ")")
    .call(d3.axisBottom(xScale))
    .append("text")    
    .attr("y", 45)
    .attr("x", width - 100)
    .attr("text-anchor", "end")
    .attr("stroke", "black")
    .text("Data Value");  
    
    g.append("line")
     .attr("x1", xScale(min))
     .attr("x2", xScale(max))
     .attr("y1", 0)
     .attr("y2", 0)
     .attr("stroke", "black")
     .attr("stroke-width", "4px");
    
    g.append("rect")     
     .attr("x", xScale(q1))     
     .attr("y", -25)
     .attr("width", (xScale(q3) - xScale(q1)))
     .attr("height", height_box)
     .attr("stroke", "black")
     .style("fill", "DimGray");
    
    g.selectAll("toto")
     .data([min, median, max])
     .enter()
     .append("line")
       .attr("x1", function(d) { return (xScale(d)) })
       .attr("x2", function(d) { return (xScale(d)) })
       .attr("y1", -25)
       .attr("y2", 25)
       .attr("stroke", "black")
       .attr("stroke-width", "4px");
    
//    svg_box.append("line")
//           .attr("x1")
  }
  
  function generate_chart_bar(data) {
    var svg_bar = d3.select("#svg_bar");
    var margin = 200;
    var width = svg_bar.attr("width") - margin;
    var height = svg_bar.attr("height") - margin;
    
    var xScale = d3.scaleBand().range([0, width]).padding(0.2);
    var yScale = d3.scaleLinear().range([height, 0]);
    var g = svg_bar.append("g")
               .attr("transform", "translate(" + 100 + "," + 100 + ")");
    
    xScale.domain(data.map(function(d) { return d.value; }));
    yScale.domain([0, d3.max(data, function(d) { return d.frequency })]);
    
    g.append("g")
     .attr("transform", "translate(0," + height + ")")
     .call(d3.axisBottom(xScale))
     .append("text")
     .attr("y", height - 250)
     .attr("x", width - 100)
     .attr("text-anchor", "end")
     .attr("stroke", "black")
     .text("Data Value");
    
    g.append("g")
     .call(d3.axisLeft(yScale)
       .ticks(data.length))       
     .append("text")
     .attr("transform", "rotate(-90)")
     .attr("y", 6)
     .attr("dy", "-5.1em")
     .attr("text-anchor", "end")
     .attr("stroke", "black")
     .text("Frequency");
    
    g.selectAll(".bar")
     .data(data)
     .enter()
       .append("rect")
       .attr("class", "bar")
       .attr("x", function(d) { return xScale(d.value); })
       .attr("y", function(d) { return yScale(d.frequency); })
       .attr("width", xScale.bandwidth())
       .attr("height", function(d) { return height - yScale(d.frequency); });
    
    svg_bar.append("text")
       .attr("transform", "translate(100, 0)")
       .attr("x", 50)
       .attr("y", 25)
       .attr("font-size", "24px")
       .text("Data Values and Frequencies");
  }
  
  function generate_charts(res) {
    var data = [];
    var data_count = res.count;
    
    //Generate JSON data for chart generators.
    for (var i = 0; i < data_count; i++) {      
      data.push({
            "value": res.data_values[i],
            "frequency": res.frequencies[i]
      });
    }
        
    generate_chart_bar(data);
    generate_chart_box(data, res);
   
    
    
     
    //DEBUG
//    for (var i = 0; i < data_count; i++) {
//      console.log(data[i].value);
//      console.log(data[i].frequency);
//    }
    
  }
  
  
  
//})


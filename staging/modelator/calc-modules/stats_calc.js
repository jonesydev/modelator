/**
 * 
 */
//var Modelator = ( function() {

  //import { reactive } from "vue";
  
  var data_values = [];  
  var datasets = [];
  var url = "localhost:8080";  
  var input_enter = document.getElementById("data_value_input");
  var is_calculated = false;  
      
  input_enter.addEventListener("keydown", event => {
    if (event.code == "enter" || event.keyCode === 13) {      
      document.getElementById("enter_data_value").click();
    }
  });
  
    
  function init_page() {
    document.getElementById("data_value_input").focus();
  }
  
  
  function decimal_count(dv) {
    var num_str = String(dv);
    var num_decimals = 0;
    
    if (num_str.includes(".")) {
      num_decimals = num_str.split(".")[1].length;
    }
    
    return num_decimals;
  }
  
  
  function is_add_data_validated(dv) {
    let is_validated = false;      
      
    if (is_calculated) {
      document.getElementById("validator_message").innerHTML = "<strong style='color:red'>Please 'Clear All' and enter a new dataset.<strong>";
    }      
    else {
      document.getElementById("validator_message").innerHTML = "";
      is_validated = true;
    }
    
    return is_validated;
  }
  
  
  function add_data_to_array(dv) {
    if (dv === "") {
      document.getElementById("validator_message").innerHTML = "<strong style='color:red'>Please enter a value.<strong>";
    }
    else {
      if (dv == 0) {
        dv = 0;
      }    
    
      if (is_add_data_validated(dv)) {
        is_calculated = false;
        data_values.push(dv);
        display_current_set();
      }
    }
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
  
    
  function limit_number_length(num, max) {
    if (num.value.length > max) {
      num.value = num.value.slice(0, max);
      document.getElementById("validator_message").innerHTML = "<strong style='color:red'>The maximum length per entry is " + max + " digits.<strong>";
    }
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
    clear_data_value_input();
    location.reload();
  }
  
  
  function backspace_data_array() {
    data_values.pop();
    display_current_set();
  }
  
  
  function is_calculate_validated() {
    let is_validated = false;
    var data_length = data_values.length;    
      
    for (var i = 0; i < data_length; i++) {
      if (data_values[i] === "") {
        document.getElementById("validator_message").innerHTML = "<strong style='color:red'>Please make sure no entries are blank.<strong>";
        document.getElementById("data_value_input").focus();
      }      
    }    

    if (is_calculated === true) {
      document.getElementById("validator_message").innerHTML = "<strong style='color:red'>Please 'Clear All' then create a new dataset.<strong>";
    }    
    else if (data_length < 3) {
      document.getElementById("validator_message").innerHTML = "<strong style='color:red'>Please enter at least three values.<strong>";
      document.getElementById("data_value_input").focus();
    }
    else {
      is_validated = true;
    }
    
    return is_validated;
  }
  
  
  function calculate() {
    if (!is_calculate_validated()) {
      is_calculated = false;
    }
    else {
      is_calculated = true;
      send_node_request();      
    }    
  }
  
  
  function add_dataset() {
    var data_length = data_values.length;
    
    if (data_length < 1) {
      document.getElementById("validator_message").innerHTML = "<strong style='color:red'>Please create a dataset.<strong>";
      document.getElementById("data_value_input").focus();
    }
    else if (data_length < 3) {
      document.getElementById("validator_message").innerHTML = "<strong style='color:red'>Please enter at least three values.<strong>";
      document.getElementById("data_value_input").focus();
    }
    else {
      ds = data_values.map((x) => x);
      datasets.push(ds);
      display_datasets();
    }    
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
    generate_frequency_table(res);
    generate_innerHTML(res);
    generate_charts(res);    
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
    
  function is_int(value) {
    return Number(value) === value && value % 1 !== 0;
  }
  
    
  function generate_frequency_table(res) {
    var freq_table = document.getElementById("frequency_table");    
    var freq_table_body = document.createElement("tbody");   
            
    var number_of_rows = res.data_values.length;    
    var data_value = 0;
    
    for (var i = 0; i < number_of_rows; i++) {
      
      data_value = res.data_values[i];
      
      var row = document.createElement("tr");
      
      // Have median row stand out.
      if (data_value === res.median) {
        row.style.fontWeight = "bold";
        row.style.fontStyle = "italic";
      }
      
      var cell_data = document.createElement("td");
      var cell_text_data = document.createTextNode(res.data_values[i]);
      cell_data.appendChild(cell_text_data);
      row.appendChild(cell_data);
      
      var cell_freq = document.createElement("td");
      var cell_text_freq = document.createTextNode(res.frequencies[i]);
      cell_freq.appendChild(cell_text_freq);
      row.appendChild(cell_freq);
      
      var cell_rel_freq = document.createElement("td");
      var cell_text_rel_freq = document.createTextNode(res.relative_frequencies[i].toFixed(3));
      cell_rel_freq.appendChild(cell_text_rel_freq);
      row.appendChild(cell_rel_freq);
      
      var cell_rel_perc = document.createElement("td");
      var cell_text_rel_perc = document.createTextNode((res.relative_frequencies[i].toFixed(3) * 100).toPrecision(3) + "%");
      cell_rel_perc.appendChild(cell_text_rel_perc);
      row.appendChild(cell_rel_perc);
      
      var cell_cum_rel_freq = document.createElement("td");
      var cell_text_cum_rel_freq = document.createTextNode(res.cumulative_relative_frequencies[i].toFixed(3));
      cell_cum_rel_freq.appendChild(cell_text_cum_rel_freq);
      row.appendChild(cell_cum_rel_freq);
      
      var cell_cum_rel_perc = document.createElement("td");
      var cell_text_cum_rel_perc = document.createTextNode((res.cumulative_relative_frequencies[i].toFixed(3) * 100).toPrecision(3) + "%");
      cell_cum_rel_perc.appendChild(cell_text_cum_rel_perc);
      row.appendChild(cell_cum_rel_perc);
      
      var cell_zscore = document.createElement("td");
      var cell_text_zscore = document.createTextNode(res.z_scores[i].toFixed(3));
      cell_zscore.appendChild(cell_text_zscore);
      row.appendChild(cell_zscore); 
      
      freq_table_body.appendChild(row);
    }
    
    freq_table.appendChild(freq_table_body);
  }
  
  function generate_innerHTML(res) {    
    document.getElementById("minimum").innerHTML = "<strong>Minimum:</strong> " + res.minimum;
    document.getElementById("maximum").innerHTML = "<strong>Maximum:</strong> " + res.maximum;
    document.getElementById("mean").innerHTML = "<strong>Mean:</strong> " + res.mean;     
    
    document.getElementById("count").innerHTML = "<strong>Count:</strong> " + res.count;
    document.getElementById("sum").innerHTML = "<strong>Sum:</strong> " + res.sum; 
    document.getElementById("standard_deviation").innerHTML = "<strong>Std Deviation:</strong> " + res.standard_deviation; 
        
    document.getElementById("range").innerHTML = "<strong>Range:</strong> " + res.range; 
    document.getElementById("variance").innerHTML = "<strong>Variance:</strong> " + res.variance; 
    document.getElementById("mode").innerHTML = "<strong>Mode:</strong> " + res.mode;
    
    document.getElementById("percentile_25").innerHTML = "<strong>1<sup>st</sup> Quartile:</strong> " + res.percentile_25;
    document.getElementById("median").innerHTML = "<strong>Median:</strong> " + res.median;
    document.getElementById("percentile_75").innerHTML = "<strong>3<sup>rd</sup> Quartile:</strong> " + res.percentile_75;
    document.getElementById("iqr").innerHTML = "<strong>IQR:</strong> " + res.iqr;
    
    document.getElementById("percentile_10").innerHTML = "<strong>10<sup>th</sup> Percentile:</strong> " + res.percentile_10;
    document.getElementById("percentile_20").innerHTML = "<strong>20<sup>th</sup> Percentile:</strong> " + res.percentile_20;
    document.getElementById("percentile_30").innerHTML = "<strong>30<sup>th</sup> Percentile:</strong> " + res.percentile_30;
    document.getElementById("percentile_40").innerHTML = "<strong>40<sup>th</sup> Percentile:</strong> " + res.percentile_40;
    
    document.getElementById("percentile_60").innerHTML = "<strong>60<sup>th</sup> Percentile:</strong> " + res.percentile_60;
    document.getElementById("percentile_70").innerHTML = "<strong>70<sup>th</sup> Percentile:</strong> " + res.percentile_70;
    document.getElementById("percentile_80").innerHTML = "<strong>80<sup>th</sup> Percentile:</strong> " + res.percentile_80;
    document.getElementById("percentile_90").innerHTML = "<strong>90<sup>th</sup> Percentile:</strong> " + res.percentile_90;      
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
  
  
  function generate_box_plot(data, res) {
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
    var count = res.count;
    var center = 100;
    var height_box = 25;
   
    var xScale = d3.scaleLinear().range([0, width]);
    var yScale = d3.scaleLinear().range([height, 0]);
    var g = svg_box.append("g")
               .attr("transform", "translate(" + 100 + "," + 100 + ")");    
    
    xScale.domain([min, max]);
    yScale.domain([0, height]);
        
    g.append("g")
    .attr("transform", "translate(0," + height + ")")
    .call(d3.axisBottom(xScale))    
    .append("text")    
    .attr("y", 45)
    .attr("x", width)
    .attr("text-anchor", "end")
    .attr("stroke", "black")
    .text("Data Value");  
    
    g.append("line")
     .attr("x1", xScale(min))
     .attr("x2", xScale(max))
     .attr("y1", 0)
     .attr("y2", 0)
     .attr("stroke", "black")
     .attr("stroke-width", "2px");
    
    g.append("rect")     
     .attr("x", xScale(q1))     
     .attr("y", -12.5)
     .attr("width", (xScale(q3) - xScale(q1)))
     .attr("height", height_box)
     .attr("stroke", "black")
     .attr("class", "box");
    
    g.selectAll("toto")
     .data([min, median, max])
     .enter()
     .append("line")
       .attr("x1", function(d) { return (xScale(d)) })
       .attr("x2", function(d) { return (xScale(d)) })
       .attr("y1", -12.5)
       .attr("y2", 12.5)
       .attr("stroke", "black")
       .attr("stroke-width", "2px");
  }
  
  function generate_bar_chart(data) {
    var svg_bar = d3.select("#svg_bar");
    var margin = 200;
    var width = svg_bar.attr("width") - margin;
    var height = svg_bar.attr("height") - margin;
    
    var xScale = d3.scaleBand().range([0, width]).padding(0.1);
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
       .ticks(5))
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
       .text("Distribution Charts");
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
        
    generate_bar_chart(data);
    generate_box_plot(data, res);    
  }  
  
//})


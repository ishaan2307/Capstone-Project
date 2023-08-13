const { SerialPort } = require('serialport');
const { ReadlineParser } = require('@serialport/parser-readline');
const port = new SerialPort({ path: 'COM3', baudRate: 9600 }, false);
const parser = port.pipe(new ReadlineParser({ delimiter: '\r\n' }));

const express = require('express');
const app = express();
const port1 = 5000;
const mongoose = require('mongoose');
const Device = require('./models/sensor');

mongoose.connect('mongodb+srv://ishaan23:ishaan23@hd.cwbw3f6.mongodb.net/', {
  useNewUrlParser: true,
  useUnifiedTopology: true
});

const bodyParser = require('body-parser');
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());
app.use(function (req, res, next) {
  res.header("Access-Control-Allow-Origin", "*");
  res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
  next();
});

app.listen(port1, () => {
  console.log(`listening on port ${port1}`);
});

parser.on('data', async data => {
  const [temperature] = data.split(" ");
  
  try {
    let device = await Device.findOne({ "id": "temp-1" });
    if (!device) {
      device = new Device({
        id: "temp-1",
        sensorData: []
      });
    }
    
    const { sensorData } = device;
    const currentTime = new Date();
    sensorData.push({ time: currentTime.toISOString(), temperature: parseFloat(temperature) });
    device.sensorData = sensorData;

    await device.save();
    console.log("Temperature data added to Device ID temp-1");
    sendTemperatureDataToPlotly("temp-1", temperature);
    
    // Convert the time to Melbourne time and log it
    console.log("Time in Melbourne:", currentTime.toLocaleString("en-AU", { timeZone: "Australia/Melbourne" }));
  } catch (err) {
    console.log(err);
  }
});

// Plotly functionality
const plotly = require('plotly')("ishaan2307", "LMyk4DSnEffbvoFiQgv1");

const temperatureData = {
  x: [],
  y: [],
  type: "scatter"
};

// Function to send temperature data to Plotly
function sendTemperatureDataToPlotly(id, temperature) {
  temperatureData.x.push(new Date().toISOString());
  temperatureData.y.push(temperature);
  const graphOptions = {
    fileopt: "overwrite",
    filename: "temperature-data-plot"
  };
  plotly.plot(temperatureData, graphOptions, function (err, msg) {
    if (err) {
      console.log(err);
    } else {
      console.log("Temperature data sent to Plotly for Device ID " + id);
      console.log("Plotly URL: " + msg.url); 
    }
  });
}

const mongoose = require('mongoose');

const deviceSchema = new mongoose.Schema({
  id: String,
  sensorData: [
    {
      time: String, // Change to String type
      temperature: Number
    }
  ]
});

module.exports = mongoose.model('Devicee', deviceSchema);

const express = require('express');
const axios = require('axios');
const router = express.Router();

// Define your API endpoint to parse the data
router.get('/categories', async (req, res) => {
  try {
    const response = await axios.get('https://stores-api.zakaz.ua/stores/48246401/categories/');
    const data = response.data;

    // If you want to do any further manipulation on the data, you can do it here
    res.json(data); // Send the raw data as the response
  } catch (error) {
    console.error(error);
    res.status(500).send('Error fetching data');
  }
});

module.exports = router;
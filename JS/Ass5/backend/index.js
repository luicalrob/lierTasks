const express = require('express');
const app = express();
const port = 3000;

// Import the router from auchanCtrl.js
const auchanRouter = require('./controller/zakazStoreCtrl/auchanCtrl'); 

// Use the router for the API routes
app.use('/api/auchan', auchanRouter); // Prefix your routes with "/api/auchan"

// Start the server
app.listen(port, () => {
  console.log(`Server running on http://localhost:${port}`);
});

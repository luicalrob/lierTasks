const mongoose = require("mongoose");

// Define the schema for your Auchan Product model
const auchanProductSchema = new mongoose.Schema(
  {
    sku: { type: String, required: true, unique: true }, // Unique SKU for product
    ean: { type: String, required: true, unique: true }, // Unique EAN for product
    title: { type: String, required: true }, // Product title
    description: { type: String, required: false }, // Product description
    price: { type: Number, required: true }, // Price of the product
    price_wholesale: { type: Number, required: false }, // Wholesale price
    discount: { type: Number, required: false }, // Discount percentage or value
    restrictions: { type: String, required: false }, // Any restrictions (e.g., shipping, region)
    category_id: { type: String, required: false }, // Category ID this product belongs to
    image_url: { type: String, required: false }, // Product image URL
  },
  { timestamps: true } // Include createdAt and updatedAt fields
);

// Create and export the model
module.exports = mongoose.model("auchanproduct", auchanProductSchema);

const mongoose = require("mongoose");

const auchancategorySchema = new mongoose.Schema({
  id: { type: String, required: true, unique: true }, // Ensure 'id' is unique
  title: { type: String, required: true },
  count: { type: Number, required: false }, // Make 'count' not required if it might not exist for all categories
  children: [{ type: mongoose.Schema.Types.ObjectId, ref: "auchancategory", default: [] }], // Referencing the same model if children are categories themselves
  description: { type: String, required: false },
  image_url: { 
    type: {
      svg: { type: String, required: false },
      png: { type: String, required: false },
      main_category_preview: { type: String, required: false }
    }, 
    required: false 
  }, // Define 'image_url' as an object with string fields
  excisable: { type: Boolean, required: false },
  is_popular: { type: Boolean, required: false },
  is_collection: { type: Boolean, required: false },
  parent_id: { type: mongoose.Schema.Types.ObjectId, ref: "auchancategory", required: false } // Referencing the same model for parent-child relationships
}, { timestamps: true });

module.exports = mongoose.model("auchancategory", auchancategorySchema);
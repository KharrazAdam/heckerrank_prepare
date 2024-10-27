// Function to set today's date
function setTodayDate() {
  const dateElement = document.getElementById("date");
  const today = new Date();
  const options = { year: "numeric", month: "long", day: "numeric" };
  dateElement.innerHTML = today.toLocaleDateString("en-US", options); // Format the date
}

// Call setTodayDate on page load
window.onload = function () {
  setTodayDate();
};

// Start function to create the table
function start() {
  // Get the input values
  const firstString = document.getElementById("first_string").value;
  const secondString = document.getElementById("second_string").value;

  // Display the strings above the table
  const stringDisplay = document.getElementById("stringDisplay");
  stringDisplay.innerHTML = `<div class="display-string"><strong> ${firstString}</strong>
                             <div"><strong>${secondString}</strong> </div>`;

  // Calculate lengths
  const firstStringLength = firstString.length;
  const secondStringLength = secondString.length;

  // Create the table HTML
  let tableHTML = "<table>";

  // Populate the table
  for (let i = 0; i <= firstStringLength; i++) {
    tableHTML += "<tr>";
    for (let j = 0; j <= secondStringLength; j++) {
      // Fill the cell with 0 for all positions
      tableHTML += `<td>0</td>`;
    }
    tableHTML += "</tr>";
  }
  tableHTML += "</table>";

  // Insert the table HTML into the scene
  const sceneDiv = document.getElementById("scene");
  sceneDiv.innerHTML = ""; // Clear previous content
  sceneDiv.innerHTML = tableHTML; // Insert the new table

  // Style the scene to ensure it appears properly
  sceneDiv.style.position = "relative"; // Ensure it stays in place
  sceneDiv.style.marginTop = "20px"; // Margin above the table
  sceneDiv.style.padding = "10px"; // Padding around the table
  sceneDiv.style.border = "2px solid #d93e2e"; // Red border for the notebook theme
  sceneDiv.style.borderRadius = "10px"; // Rounded corners
}

function updateTable() {
  const sceneDiv = document.getElementById("scene");
  const cells = sceneDiv.getElementsByTagName("td");

  // Update each cell value (for example, incrementing the value by 1)
  for (let cell of cells) {
    cell.innerText = parseInt(cell.innerText) + 1; // Increment each cell's value
  }
}

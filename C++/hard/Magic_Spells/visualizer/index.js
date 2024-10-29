// Cache DOM elements
const firstStringInput = document.getElementById("first_string");
const secondStringInput = document.getElementById("second_string");
const currentDateDisplay = document.getElementById("current-date");
const firstStringDisplay = document.getElementById("first-string-display");
const secondStringDisplay = document.getElementById("second-string-display");
const explanationDiv = document.getElementById("explanation");
const sceneContainer = document.getElementById("scene");
const startButton = document.querySelector("button[onclick='start()']"); // Cache start button

let isStarted = false;
let ix = [];
let m, n, f, g;
let lastUpdatedCell = { row: null, col: null };
let LCS = "";
let isLCSshowed = false;

// Helper function to initialize LCS variables
function initializeLCS() {
  m = firstStringInput.value.length;
  n = secondStringInput.value.length;
  ix = Array(m + 1)
    .fill()
    .map(() => Array(n + 1).fill(0)); // Reset LCS matrix
  f = 1;
  g = 1;
  lastUpdatedCell = { row: null, col: null };
}

function createStyledSpan(text, fontWeight = "bold", fontSize = "20px") {
  const span = document.createElement("span");
  span.style.fontWeight = fontWeight;
  span.style.fontSize = fontSize;
  span.innerText = text;
  return span;
}

function start() {
  if (!isStarted) {
    // First time start
    currentDateDisplay.innerText = new Date().toLocaleDateString();
    startButton.innerText = "Restart"; // Change button to "Restart"
    isStarted = true;
  } else {
    // Reset for restart
    firstStringDisplay.innerHTML = "";
    secondStringDisplay.innerHTML = "";
    explanationDiv.innerHTML = "";
    sceneContainer.querySelector("table")?.remove(); // Remove existing table
    isStarted = false; // Reset `isStarted`
  }

  // Display the new input strings
  firstStringDisplay.appendChild(createStyledSpan(firstStringInput.value));
  secondStringDisplay.appendChild(createStyledSpan(secondStringInput.value));

  // Initialize LCS variables and display the empty table
  initializeLCS();
  updateTable();
}

function updateTable() {
  const existingTable = sceneContainer.querySelector("table");
  if (existingTable) existingTable.remove();

  const table = document.createElement("table");

  // Create the header row with an extra empty cell for alignment
  const headerRow = document.createElement("tr");
  const emptyCell = document.createElement("th"); // Top-left corner cell, empty
  headerRow.appendChild(emptyCell);

  // Add another empty cell to shift secondString characters to the right by one
  const extraEmptyCell = document.createElement("th");
  headerRow.appendChild(extraEmptyCell);

  // Append characters of secondString as column headers, shifted to the right
  for (let j = 0; j < n; j++) {
    const headerCell = document.createElement("th");
    headerCell.innerText = secondStringInput.value[j] || ""; // Fill with characters from secondString
    if (j >= g - 2) headerCell.style.color = "blue";
    headerRow.appendChild(headerCell);
  }
  table.appendChild(headerRow);

  // Populate rows with characters of firstString and the LCS matrix values
  for (let i = 0; i <= m; i++) {
    const row = document.createElement("tr");

    // Add row header for firstString characters
    const rowHeaderCell = document.createElement("th");
    rowHeaderCell.innerText = i > 0 ? firstStringInput.value[i - 1] : ""; // Fill with characters from firstString
    if (i >= f) rowHeaderCell.style.color = "red";
    row.appendChild(rowHeaderCell);

    for (let j = 0; j <= n; j++) {
      const cell = document.createElement("td");
      cell.innerText = `${ix[i][j]}`; // Use the ix array to fill the table
      if (i === lastUpdatedCell.row && j === lastUpdatedCell.col) {
        cell.classList.add("updated-cell");
      }
      row.appendChild(cell);
    }
    table.appendChild(row);
  }
  sceneContainer.appendChild(table);
}

function highlightCharacters() {
  const highlightString = (displayElement, string, index, color) => {
    displayElement.innerHTML = ""; // Clear previous highlights
    for (let i = 0; i < string.length; i++) {
      const charSpan = document.createElement("span");
      charSpan.innerText = string[i];
      if (i === index) charSpan.style.color = color; // Highlight current character
      displayElement.appendChild(charSpan);
    }
  };

  highlightString(firstStringDisplay, firstStringInput.value, f - 1, "red");
  highlightString(secondStringDisplay, secondStringInput.value, g - 1, "blue");
}

function highlightLCS() {
  let i = m,
    j = n;
  const lcsIndicesFirst = [];
  const lcsIndicesSecond = [];

  // Trace back through the LCS matrix to find matching indices
  while (i > 0 && j > 0) {
    if (firstStringInput.value[i - 1] === secondStringInput.value[j - 1]) {
      lcsIndicesFirst.push(i - 1);
      lcsIndicesSecond.push(j - 1);
      i--;
      j--;
    } else if (ix[i - 1][j] > ix[i][j - 1]) {
      i--;
    } else {
      j--;
    }
  }

  // Highlight matching characters in the input strings
  const highlightString = (displayElement, string, indices, color) => {
    displayElement.innerHTML = "";
    for (let k = 0; k < string.length; k++) {
      const charSpan = document.createElement("span");
      charSpan.innerText = string[k];
      if (indices.includes(k)) charSpan.style.color = color; // Highlight LCS character
      displayElement.appendChild(charSpan);
    }
  };

  highlightString(
    firstStringDisplay,
    firstStringInput.value,
    lcsIndicesFirst,
    "green"
  );
  highlightString(
    secondStringDisplay,
    secondStringInput.value,
    lcsIndicesSecond,
    "green"
  );

  // Highlight corresponding LCS cells in the table
  for (let k = 0; k < lcsIndicesFirst.length; k++) {
    const row = lcsIndicesFirst[k] + 2; // Adjusted for 1-indexed rows
    const col = lcsIndicesSecond[k] + 2; // Adjusted for 1-indexed columns
    const tableCell = sceneContainer.querySelector(
      `table tr:nth-child(${row + 1}) td:nth-child(${col + 1})`
    );
    if (tableCell) {
      tableCell.style.backgroundColor = "green";
      tableCell.style.color = "white";
      tableCell.style.fontWeight = "white";
    }
  }

  // Add explanations for each LCS letter at the end
  explanationDiv.innerHTML = "<h3>Explanation of LCS Letters:</h3>"; // Clear and add header
  for (let k = lcsIndicesFirst.length - 1; k >= 0; k--) {
    const explanationText = document.createElement("p");
    const firstStringChar = firstStringInput.value[lcsIndicesFirst[k]];
    const secondStringChar = secondStringInput.value[lcsIndicesSecond[k]];

    explanationText.innerHTML = `Matched letter "<strong>${firstStringChar}</strong>" at position <strong>${
      lcsIndicesFirst[k] + 1
    }</strong> in <em>firstString</em> and position <strong>${
      lcsIndicesSecond[k] + 1
    }</strong> in <em>secondString</em>.`;
    explanationText.style.fontSize = "16px";
    explanationText.style.color = "#333";
    explanationDiv.appendChild(explanationText);
  }
}

document.addEventListener("keydown", (event) => {
  if (event.key === "ArrowRight") moveRight();
  else if (event.key === "ArrowLeft") moveLeft();
});

function moveRight() {
  if (firstStringInput.value[f - 1] === secondStringInput.value[g - 1]) {
    ix[f][g] = ix[f - 1][g - 1] + 1;
  } else {
    ix[f][g] = Math.max(ix[f - 1][g], ix[f][g - 1]);
  }

  lastUpdatedCell = { row: f, col: g }; // Set last updated cell
  updateExplanation();
  highlightCharacters();

  g++;
  if (g > n) {
    g = 1;
    f++;
  }
  updateTable();
  if (f > m) highlightLCS();
}

function moveLeft() {
  if (g === 1 && f > 1) {
    g = n;
    f--;
  } else if (g > 1) {
    g--;
  }
  lastUpdatedCell = { row: f, col: g };
  updateExplanation();
  highlightCharacters();
  updateTable();
}

function updateExplanation() {
  const charFromFirst = firstStringInput.value[f - 1] || "";
  const charFromSecond = secondStringInput.value[g - 1] || "";

  if (charFromFirst && charFromSecond) {
    if (charFromFirst === charFromSecond) {
      explanationDiv.innerText = `Matched "${charFromFirst}" in both strings.`;
    } else {
      explanationDiv.innerText = `No match at "${charFromFirst}" and "${charFromSecond}".`;
    }
  } else {
    explanationDiv.innerText = "Reached the end of the strings.";
  }
}

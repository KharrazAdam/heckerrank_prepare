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

  for (let i = 0; i <= m; i++) {
    const row = document.createElement("tr");
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
  explanationDiv.innerHTML = ""; // Clear previous explanation

  const explanationText = document.createElement("p");
  explanationText.style.fontSize = "18px";
  explanationText.style.color = "#333";

  explanationText.innerHTML =
    charFromFirst === charFromSecond
      ? `Characters match: "<strong>${charFromFirst}</strong>" from <em>firstString</em> and "<strong>${charFromSecond}</strong>" from <em>secondString</em>. This increases LCS by 1. Current LCS value at (${f}, ${g}) is <strong>${ix[f][g]}</strong>.`
      : `Characters do not match: "<strong>${charFromFirst}</strong>" from <em>firstString</em> and "<strong>${charFromSecond}</strong>" from <em>secondString</em>. The LCS value remains the maximum of the previous values, which is <strong>${ix[f][g]}</strong> at (${f}, ${g}).`;

  explanationDiv.appendChild(explanationText);
}

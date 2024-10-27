// Get the input values
const firstString = document.getElementById("first_string").value;
const secondString = document.getElementById("second_string").value;

const m = firstString.length;
const n = secondString.length;
let isStarted = false;
let ix = Array.from({ length: m + 1 }, () => Array(n + 1).fill(0)); // Initialize ix for LCS

function updateStrings(text) {
  const span = document.createElement("span");
  span.style.fontWeight = "bold";
  span.style.fontSize = "20px";
  span.innerText = text;
  return span;
}

function start() {
  // Display current date
  if (isStarted) return;
  document.getElementById("current-date").innerText =
    new Date().toLocaleDateString();

  document
    .querySelector("#first-string-display")
    .appendChild(updateStrings(firstString));
  document
    .querySelector("#second-string-display")
    .appendChild(updateStrings(secondString));

  // Calculate the LCS and update the ix array

  // Update the table to reflect the current LCS results
  updateTable();
  isStarted = true;
}

function updateTable() {
  const existingTable = document.querySelector("#scene table");
  if (existingTable) {
    existingTable.remove();
  }

  const table = document.createElement("table");

  for (let i = 0; i <= m; i++) {
    const row = document.createElement("tr");

    for (let j = 0; j <= n; j++) {
      const cell = document.createElement("td");
      cell.innerText = `${ix[i][j]}`; // Use the ix array to fill the table
      row.appendChild(cell);
    }

    table.appendChild(row);
  }

  document.getElementById("scene").appendChild(table);
}

function calculateLCS(X, Y) {
  const localIx = ix;
  for (let i = 1; i <= X.length; i++) {
    for (let j = 1; j <= Y.length; j++) {
      if (X[i - 1] === Y[j - 1]) {
        localIx[i][j] = localIx[i - 1][j - 1] + 1;
      } else {
        localIx[i][j] = Math.max(localIx[i - 1][j], localIx[i][j - 1]);
      }
    }
  }

  ix = localIx;
}

let f = 1;
let g = 1;
function moveRight() {
  const localIx = ix;
  if (firstString[f - 1] === secondString[g - 1]) {
    localIx[f][g] = localIx[f - 1][g - 1] + 1;
  } else {
    localIx[f][g] = Math.max(localIx[f - 1][g], localIx[f][g - 1]);
  }
  g++;
  if (g > n) {
    g = 1;
    f++;
  }
  updateTable(); // Ensure the table updates when moving
}

function moveLeft() {
  const localIx = ix;

  if (g == 1 && f > 1) {
    g = n;
    f--;
  } else if (g > 1) g--;
  localIx[f][g] = 0;
  updateTable();
}

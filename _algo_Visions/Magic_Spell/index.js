// Cache DOM elements
const DOM = {
  firstStringInput: document.getElementById("first_string"),
  secondStringInput: document.getElementById("second_string"),
  currentDateDisplay: document.getElementById("current-date"),
  firstStringDisplay: document.getElementById("first-string-display"),
  secondStringDisplay: document.getElementById("second-string-display"),
  explanationDiv: document.getElementById("explanation"),
  sceneContainer: document.getElementById("scene"),
  startButton: document.querySelector("button[onclick='start()']"), // Cache start button
};

let isStarted = false;
let ix = [];
let m, n, f, g;
let lastUpdatedCell = { row: null, col: null };
let LCS = "";
let isLCSshowed = false;

// Helper function to initialize LCS variables
function initializeLCS() {
  m = DOM.firstStringInput.value.length;
  n = DOM.secondStringInput.value.length;
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
    DOM.currentDateDisplay.innerText = new Date().toLocaleDateString();
    DOM.startButton.innerText = "Restart"; // Change button to "Restart"
    isStarted = true;
  } else {
    // Reset for restart
    DOM.firstStringDisplay.innerHTML = "";
    DOM.secondStringDisplay.innerHTML = "";

    DOM.explanationDiv.innerHTML = "";
    DOM.sceneContainer.querySelector("table")?.remove(); // Remove existing table
    isStarted = false; // Reset `isStarted`
  }

  // Display the new input strings
  DOM.firstStringDisplay.appendChild(
    createStyledSpan(DOM.firstStringInput.value)
  );
  DOM.secondStringDisplay.appendChild(
    createStyledSpan(DOM.secondStringInput.value)
  );

  // Initialize LCS variables and display the empty table
  initializeLCS();
  updateTable();
}

function updateTable() {
  const existingTable = DOM.sceneContainer.querySelector("table");
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
    headerCell.innerText = DOM.secondStringInput.value[j] || ""; // Fill with characters from secondString

    if (j >= g - 1) headerCell.style.color = "blue"; // Correct and functional
    headerRow.appendChild(headerCell);
  }
  table.appendChild(headerRow);

  // Populate rows with characters of firstString and the LCS matrix values
  for (let i = 0; i <= m; i++) {
    const row = document.createElement("tr");

    // Add row header for firstString characters
    const rowHeaderCell = document.createElement("th");
    rowHeaderCell.innerText = i > 0 ? DOM.firstStringInput.value[i - 1] : ""; // Fill with characters from firstString
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
  DOM.sceneContainer.appendChild(table);
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

  highlightString(
    DOM.firstStringDisplay,
    DOM.firstStringInput.value,
    f - 1,
    "red"
  );
  highlightString(
    DOM.secondStringDisplay,
    DOM.secondStringInput.value,
    g - 1,
    "blue"
  );
}

function highlightLCS() {
  let i = m,
    j = n;
  const lcsIndicesFirst = [];
  const lcsIndicesSecond = [];

  // Trace back through the LCS matrix to find matching indices
  while (i > 0 && j > 0) {
    if (
      DOM.firstStringInput.value[i - 1] === DOM.secondStringInput.value[j - 1]
    ) {
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
    DOM.firstStringDisplay,
    DOM.firstStringInput.value,
    lcsIndicesFirst,
    "green"
  );
  highlightString(
    DOM.secondStringDisplay,
    DOM.secondStringInput.value,
    lcsIndicesSecond,
    "green"
  );

  // Highlight corresponding LCS cells in the table

  for (let k = 0; k < lcsIndicesFirst.length; k++) {
    const row = lcsIndicesFirst[k] + 2; // Adjusted for 1-indexed rows
    const col = lcsIndicesSecond[k] + 2; // Adjusted for 1-indexed columns
    const tableCell = DOM.sceneContainer.querySelector(
      `table tr:nth-child(${row + 1}) td:nth-child(${col + 1})`
    );
    if (tableCell) {
      tableCell.style.backgroundColor = "green";
      tableCell.style.color = "white";
      tableCell.style.fontWeight = "white";
    }
  }

  // Highlight only the cells that contain LCS characters in the first row
  const tabllo = DOM.sceneContainer.querySelector("table");
  const firstRow = tabllo.rows[0]; // Assuming the first row (index 1) is the one you want to highlight (after header)
  if (firstRow)
    lcsIndicesSecond.forEach((index) => {
      const cell = firstRow.cells[index + 2]; // Get the corresponding cell based on the LCS index
      if (cell) {
        cell.style.color = "green";
        cell.style.fontWeight = "bold";
        cell.style.backgroundColor = "pink";
      }
    });
  // const firstCol = tabllo.col[0]; // Assuming the first row (index 1) is the one you want to highlight (after header)
  // if (firstCol)
  lcsIndicesFirst.forEach((index) => {
    const cell = tabllo.rows[index + 2].cells[0]; // Access the first column (index 0)
    if (cell) {
      cell.style.color = "green"; // Change text color to green
      cell.style.fontWeight = "bold"; // Make the text bold
      cell.style.backgroundColor = "pink"; // Change background color to pink
    }
  });
  // Add explanations for each LCS letter at the end
  DOM.explanationDiv.innerHTML = "<h3>Explanation of LCS Letters:</h3>"; // Clear and add header
  for (let k = lcsIndicesFirst.length - 1; k >= 0; k--) {
    const explanationText = document.createElement("p");
    const firstStringChar = DOM.firstStringInput.value[lcsIndicesFirst[k]];

    explanationText.innerHTML = `Matched letter "<strong>${firstStringChar}</strong>" at position <strong>${
      lcsIndicesFirst[k] + 1
    }</strong> in <em>firstString</em> and position <strong>${
      lcsIndicesSecond[k] + 1
    }</strong> in <em>secondString</em>.`;
    explanationText.style.fontSize = "16px";
    explanationText.style.color = "#333";
    DOM.explanationDiv.appendChild(explanationText);
  }

  // Detailed explanation of backtracking
  const backtrackingExplanation = document.createElement("p");
  backtrackingExplanation.innerHTML = `
	  <strong>Backtracking Explanation:</strong><br>
	  <p style="text-align: center">The backtracking process begins after the LCS matrix (ix) has been fully populated. 
	  Each cell in the matrix represents the length of the LCS up to that point in the respective strings. 
	  We start from the bottom-right corner of the matrix (length of the first string (m) = ${m}, length of the second string (n) = ${n}) and iterate back through the matrix:</p>
	  <ul>
		<li>When characters match (firstString[i-1] === secondString[j-1]), they are part of the LCS. We store these indices and move diagonally up-left (i--, j--).</li>
		<li>If the characters do not match, we check the values in the matrix: 
			<ul>
			  <li>If the value above (matrix[i-1][j]) is greater, we move up (i--).</li>
			  <li>Otherwise, we move left (j--).</li>
			</ul>
		</li>
		<li>This process continues until we reach either the first row or the first column, indicating we've traversed one of the strings completely.</li>
	  </ul>
	`;
  backtrackingExplanation.style.fontSize = "14px";
  backtrackingExplanation.style.color = "#666";
  DOM.explanationDiv.appendChild(backtrackingExplanation);
  highlightLCSCharacters();
}

document.addEventListener("keydown", (event) => {
  if (event.key === "ArrowRight") moveRight();
  else if (event.key === "ArrowLeft") moveLeft();
  else if (event.key === "ArrowDown") moveEnd();
  else if (event.key === "ArrowUp") moveStart();
});

function moveStart() {
  start();
  DOM.firstStringDisplay.innerHTML = "";
  DOM.secondStringDisplay.innerHTML = "";
  DOM.explanationDiv.innerHTML = "";
}

function moveEnd() {
  // Populate the LCS matrix before moving to the end
  if (!isStarted) start();
  for (let i = 1; i <= m; i++) {
    for (let j = 1; j <= n; j++) {
      if (
        DOM.firstStringInput.value[i - 1] === DOM.secondStringInput.value[j - 1]
      ) {
        ix[i][j] = ix[i - 1][j - 1] + 1; // Increment if characters match
      } else {
        ix[i][j] = Math.max(ix[i - 1][j], ix[i][j - 1]); // Take the max from the left or above
      }
    }
  }

  // Set f and g to the length of their respective strings
  f = m; // Set f to the length of the first string
  g = n; // Set g to the length of the second string

  lastUpdatedCell = { row: f, col: g }; // Set last updated cell to the end
  updateExplanation();
  highlightCharacters();
  updateTable();

  // Highlight the LCS after reaching the end
  if (f > 0 && g > 0) highlightLCS();
}

function moveRight() {
  if (!isStarted) start();
  if (
    DOM.firstStringInput.value[f - 1] === DOM.secondStringInput.value[g - 1]
  ) {
    ix[f][g] = ix[f - 1][g - 1] + 1;
  } else {
    ix[f][g] = Math.max(ix[f - 1][g], ix[f][g - 1]);
  }

  lastUpdatedCell = { row: f, col: g }; // Set last updated cell
  updateExplanation();
  highlightCharacters();

  updateTable();
  g++;
  if (g > n) {
    g = 1;
    f++;
  }
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
  const charFromFirst = DOM.firstStringInput.value[f - 1] || "";
  const charFromSecond = DOM.secondStringInput.value[g - 1] || "";

  if (charFromFirst && charFromSecond) {
    if (charFromFirst === charFromSecond) {
      DOM.explanationDiv.innerText = `Matched "${charFromFirst}" in both strings.`;
    } else {
      DOM.explanationDiv.innerText = `No match at "${charFromFirst}" and "${charFromSecond}".`;
    }
  } else {
    DOM.explanationDiv.innerText = "Reached the end of the strings.";
  }
}

function highlightLCSCharacters() {
  // Check if the length of the first string is greater than the second string
  if (DOM.firstStringInput.value.length > DOM.secondStringInput.value.length) {
    let i = m,
      j = n;

    // Initialize arrays to hold LCS indices
    const lcsIndicesFirst = [];
    const lcsIndicesSecond = [];

    // Trace back through the LCS matrix to find matching indices
    while (i > 0 && j > 0) {
      if (
        DOM.firstStringInput.value[i - 1] === DOM.secondStringInput.value[j - 1]
      ) {
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
    // Highlight matching characters in the input strings if any
    if (lcsIndicesFirst.length > 0 && lcsIndicesSecond.length > 0) {
      const highlightString = (displayElement, string, indices, color) => {
        displayElement.innerHTML = "";
        for (let k = 0; k < string.length; k++) {
          const charSpan = document.createElement("span");
          charSpan.innerText = string[k];
          charSpan.style.color = indices.includes(k) ? color : "black"; // Highlight LCS character
          displayElement.appendChild(charSpan);
        }
      };

      highlightString(
        DOM.firstStringDisplay,
        DOM.firstStringInput.value,
        lcsIndicesFirst,
        "green"
      );
      highlightString(
        DOM.secondStringDisplay,
        DOM.secondStringInput.value,
        lcsIndicesSecond,
        "green"
      );

      // Explanation of LCS letters
      DOM.explanationDiv.innerHTML = "<h3>Explanation of LCS Letters:</h3>"; // Clear and add header
      for (let k = lcsIndicesFirst.length - 1; k >= 0; k--) {
        const explanationText = document.createElement("p");
        const firstStringChar = DOM.firstStringInput.value[lcsIndicesFirst[k]];

        explanationText.innerHTML = `Matched letter "<strong>${firstStringChar}</strong>" at position <strong>${
          lcsIndicesFirst[k] + 1
        }</strong> in <em>firstString</em> and position <strong>${
          lcsIndicesSecond[k] + 1
        }</strong> in <em>secondString</em>.`;
        explanationText.style.fontSize = "16px";
        explanationText.style.color = "#333";
        DOM.explanationDiv.appendChild(explanationText);
      }
    } else {
      DOM.explanationDiv.innerHTML = "<h3>No common subsequence found!</h3>";
    }
  }
}

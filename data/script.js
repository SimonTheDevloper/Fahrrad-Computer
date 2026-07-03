const ledBtn = document.getElementById("ledBtn");

let ledStatus = false;

ledBtn.addEventListener("click", toggleLed);

async function toggleLed() {
    try {
        const url = ledStatus ? "/tests/ledoff" : "/tests/ledon";

        const response = await fetch(url);
        if (!response) {
            throw new Error("HTTP mistake");
        }
        const data = await response.json();

        console.log(data);

        ledStatus = !ledStatus;
        ledBtn.textContent = ledStatus
            ? "LED off"
            : "LED on";
    } catch (err) {
        console.log("There is a mistake:", err);
    }
}


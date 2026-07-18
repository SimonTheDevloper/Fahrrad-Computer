const downloadBtn = document.getElementById("downloadBtn");

downloadBtn.addEventListener("click", () => {
    const link = document.createElement("a");
    link.href = "/letzteFahrt";
    link.download = "letzteFahrt.csv";
    document.body.appendChild(link);
    link.click();
    document.body.removeChild(link);
});

document.addEventListener("DOMContentLoaded", ladeAlleFahrten);

async function ladeAlleFahrten() {
    const listElement = document.getElementById("fahrtListe");

    try {
        const response = await fetch("/alleFahrten");
        if (!response.ok) throw new Error("Netzwerkfehler");

        let fahrten = await response.json();

        listElement.innerHTML = "";

        if (fahrten.length === 0) {
            listElement.innerHTML = `<li class="empty-msg">Noch keine Fahrten.</li>`;
            return;
        }

        fahrten.sort((a, b) => { //damit es nach der größe sotiert wird
            const startA = a.indexOf("-") + 1;
            const endeA = a.indexOf(".");

            const numA = parseInt(a.substring(startA, endeA));

            const startB = b.indexOf("-") + 1;
            const endeB = b.indexOf(".");
            const numB = parseInt(b.substring(startB, endeB));

            return numB - numA;
        });

        fahrten.forEach(dateiName => {
            const li = document.createElement("li");

            const span = document.createElement("span");
            span.className = "ride-name";
            span.textContent = dateiName;

            const btn = document.createElement("button");
            btn.className = "btn-small";
            btn.textContent = "Laden";

            btn.addEventListener("click", () => {
                const link = document.createElement("a");
                link.href = `/download?file=${dateiName}`;
                document.body.appendChild(link);
                link.click();
                document.body.removeChild(link);
            }); q

            li.appendChild(span);
            li.appendChild(btn);
            listElement.appendChild(li);
        });

    } catch (error) {
        console.error("Fehler beim Laden der Fahrten:", error);
        listElement.innerHTML = `<li class="empty-msg">Fehler beim Laden der Liste.</li>`;
    }
}
const downloadBtn = document.getElementById("downloadBtn");

downloadBtn.addEventListener("click", () => {
    const link = document.createElement("a");
    link.href = "/letzteFahrt";
    link.download = "letzteFahrt.csv";
    document.body.appendChild(link);
    link.click();
    document.body.removeChild(link);
});

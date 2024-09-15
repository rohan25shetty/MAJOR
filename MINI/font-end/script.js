document.addEventListener("DOMContentLoaded", function() {
    const batteryStatusElement = document.getElementById("batteryStatus");
    const voltageElement = document.getElementById("voltage");
    const currentElement = document.getElementById("current");
    const temperatureElement = document.getElementById("temperature");

    const batteryStatusBar = document.getElementById("batteryStatusBar");
    const voltageBar = document.getElementById("voltageBar");
    const currentBar = document.getElementById("currentBar");
    const temperatureBar = document.getElementById("temperatureBar");

    function fetchData() {
        // Simulating fetching data with dummy variables
        const data = {
            batteryPercentage: Math.floor(Math.random() * 101), // Random value between 0 and 100
            voltagePercentage: Math.floor(Math.random() * 101),
            currentPercentage: Math.floor(Math.random() * 101),
            temperaturePercentage: Math.floor(Math.random() * 101),
            batteryStatus: Math.random() > 0.5, // Random boolean
            voltage: (Math.random() * 100).toFixed(2), // Random voltage value
            current: (Math.random() * 10).toFixed(2), // Random current value
            temperature: (Math.random() * 100).toFixed(2) // Random temperature value
        };

        // Update UI with fetched data
        updateBatteryStatus(data.batteryPercentage);
        updateVoltage(data.voltagePercentage);
        updateCurrent(data.currentPercentage);
        updateTemperature(data.temperaturePercentage);

        batteryStatusElement.textContent = data.batteryStatus ? "Healthy" : "Needs Maintenance";
        voltageElement.textContent = data.voltage + " V";
        currentElement.textContent = data.current + " A";
        temperatureElement.textContent = data.temperature + " °C";
    }

    function updateBatteryStatus(percentage) {
        batteryStatusBar.style.width = percentage + '%';
    }

    function updateVoltage(percentage) {
        voltageBar.style.width = percentage + '%';
    }

    function updateCurrent(percentage) {
        currentBar.style.width = percentage + '%';
    }

    function updateTemperature(percentage) {
        temperatureBar.style.width = percentage + '%';
    }

    // Fetch data every 5 seconds
    setInterval(fetchData, 5000);
    fetchData(); // Initial fetch
});

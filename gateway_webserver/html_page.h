//=====================
//HTML code for webpage
//=====================
const char webpageCode[] PROGMEM =
R"=====(
<!DOCTYPE html>
<html lang='en'>
<head>
  <meta charset='UTF-8'>
  <meta http-equiv='X-UA-Compatible' content='IE=edge'>
  <meta name='viewport' content='width=device-width, initial-scale=1.0'>
  <title>OAU's Weather Station</title>
  <link rel='preconnect' href='https://fonts.googleapis.com'>
  <link rel='preconnect' href='https://fonts.gstatic.com' crossorigin>
  <link href='https://fonts.googleapis.com/css2?family=Open+Sans:wght@400;500;700&display=swap' rel='stylesheet'>
  <script src="https://cdn.jsdelivr.net/npm/chart.js@4.0.1/dist/chart.umd.min.js"></script>
</head>
<body>
  <img class='logo' src='https://networks.au-ibar.org/show/obafemi-awolowo-university-ife-nigeria/wiki-image/AU+REC+logos+%2841%29.png' />
  <h1>OAU Loral Wireless Weather Station</h1>
  <h2>Group</h2>
  <div class='data-container-m'>
    <div class='data'>
      <h3 id='day' class='data-header'></h3>
      <p id='date' class='data-value'></p>
    </div>
    <div class='data'>
      <h3 class='data-header'>Temperature</h3>
      <p class='data-value' id='temperature'>33<sup>o</sup>C</p>
    </div>
  </div>
  
  <div class='other-data'>
    <div class='data'>
      <h3 class='data-header'>Humidity</h3>
      <p class='data-value' id='humidity'></p>
    </div>
    <div class='data'>
      <h3 class='data-header'>Pressure</h3>
      <p class='data-value' id='pressure'></p>
    </div>
    <div class='data'>
      <h3 class='data-header'>Altitude</h3>
      <p class='data-value' id='altitude'></p>
    </div>
    <div class='data'>
      <h3 class='data-header'>Dew Point</h3>
      <p class='data-value' id='dewPoint'></p>
    </div>
    <div class='data'>
      <h3 class='data-header'>Rainfall</h3>
      <p class='data-value' id='rainfall'></p>
    </div>
    <div class='data'>
      <h3 class='data-header'>Light</h3>
      <p class='data-value' id='lux'></p>
    </div>
  </div>

  <canvas id="chart"></canvas>

  <style>
    * {
      box-sizing: border-box;
      color: #fff;
      padding: 0;
      margin: 0;
      font-family: 'Open Sans', sans-serif;
    }
    body {
      /* background-color: #08082B; */
      padding: 15px;
      text-align: center;
    }
    .logo {
      width: 7rem;
    }
    h1 {
      color: #010080;
      font-size: 1.5rem;
    }
    h2 {
      color: #010080;
      font-size: 1rem;
      font-weight: 500;
    }
    p {
      font-size: 0.8rem;
      font-weight: 400;
    }
    .data-container-m {
      margin: 10px auto;
      border-radius: 10px;
      display: flex;
      /* flex-direction: spa; */
      justify-content: space-between;
      background-color: #010080;
      width: max-content;
    }
    .data {
      /* margin-left: 20px; */
      padding: 10px;
      width: 10rem;
    }
    .data-container-m .data:last-of-type {
      border-left: 2px solid #fff;
    }

    .data-header {
      font-weight: 500;
      margin-bottom: 5px;
    }

    .other-data {
      width: 100%;
      display: flex;
      flex-wrap: wrap;
      justify-content: center;
      column-gap: 10px;
      row-gap: 10px;
      margin: 0 auto;
      margin-top: 30px;
      max-width: 50rem;
    }

    .other-data .data {
      padding: 10px;
      width: 10rem;
      border: 1px solid #010080;
      border-radius: 10px;
    }

    .other-data .data-value, .other-data .data-header, .other-data .data-value sup {
      color: #010080;
    }
  </style>
    <script defer>
      const dateObj = new Date();
      const day = dateObj.getDay();
      const month = dateObj.getMonth();
      const date = dateObj.getDate();

      const daysMap = {
        0: 'Sunday',
        1: 'Monday',
        2: 'Tuesday',
        3: 'Wednesday',
        4: 'Thursday',
        5: 'Friday',
        6: 'Saturday',
      };

      const monthMap = {
        0: 'Jan',
        1: 'Feb',
        2: 'Mar',
        3: 'Apr',
        4: 'May',
        5: 'Jun',
        6: 'Jul',
        7: 'Aug',
        8: 'Sept',
        9: 'Oct',
        10: 'Nov',
        11: 'Dec',
      }

      const dateEl = document.getElementById('date');
      dateEl.innerText = `${date} ${monthMap[month]}`;

      const dayEl = document.getElementById('day');
      dayEl.innerText = daysMap[day];

      const InitWebSocket = () => {
          websock = new WebSocket('ws://'+window.location.hostname+':81/'); 
          websock.onmessage = function(evt)
          {
            JSONobj = JSON.parse(evt.data);

            const { lux, rainfall, dewPoint, humidity, altitude, pressure, temperature } = JSONobj;
            
            document.getElementById('temperature').innerHTML = `${temperature}<sup>o</sup>C`;
            document.getElementById('humidity').innerHTML = `${humidity}%`;
            document.getElementById('pressure').innerHTML = `${pressure}hPa`;
            document.getElementById('altitude').innerHTML = `${altitude}m`;
            document.getElementById('dewPoint').innerHTML = `${dewPoint}<sup>o</sup>C`;
            document.getElementById('rainfall').innerHTML = `${rainfall}%`;
            document.getElementById('lux').innerHTML = `${lux}ls`;

            
            const dateTime = new Date();
            const time = `${dateTime.getHours}:${dateTime.getMinutes}:${dateTime.getSeconds}`;

            console.log("HEYYY", JSONobj, time);
          }
          
      }
      InitWebSocket()
    </script>
  </body>
</html>
)=====";

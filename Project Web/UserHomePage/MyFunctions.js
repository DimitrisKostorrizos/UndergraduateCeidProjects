function GraphSetter()
{
    var today = new Date();
    var mm = String(today.getMonth()).padStart(2, '0');
    var months = ["Ιανουάριος", "Φεβρουάριος", "Μάρτιος", "Απρίλιος", "Μάϊος", "Ιούνιος", "Ιούλιος", "Αύγουστος", "Σεπτέμβριος", "Οκτώβριος", "Νοέμβριος","Δεκέμβριος"];
    labels = [];
    for(let index = 0; index < 12; index++)
    {
        if(index <= mm)
        {
            labels.push(months[index]);
        }
        else
        {
            labels.unshift(months[index]);
        }
    }
    var ctx = document.getElementById('myChart').getContext('2d');
    var myChart = new Chart(ctx, {
        type: 'line',
        data: {
            labels: labels,
            datasets: [{
                label: "% of activity per month",
                data: [33, 49.2, 55, 67, 22, 11, 45, 78, 21, 45, 67, 33],
                backgroundColor: [
                    "rgba(36, 32, 56, 0.2)"
                ],
                borderColor: [
                    "rgba(36, 32, 56, 1)"
                ],
                borderWidth: 2,
                lineTension: 0,
                pointBorderWidth: 2,
                pointBorderColor: "rgba(36, 32, 56, 1)"
            }]
        },
        options: {
            scales: {
                yAxes: [{
                    ticks: {
                        beginAtZero: true
                    }
                }]
            }
        }
    });
}

function LeaderboardSetter(firstid,secondid,thirdid,userid,userposition)
{
    document.getElementById(firstid).innerHTML = "first";
    document.getElementById(secondid).innerHTML = "Second";
    document.getElementById(thirdid).innerHTML = "Third";
    document.getElementById(userid).innerHTML = "User";
    document.getElementById(userposition).innerHTML = "56";
}
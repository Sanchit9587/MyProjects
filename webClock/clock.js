function getTime()
{
    let time=new Date();//gets the object which contains the time on the local machine
    let timeString=formatTime(time);
    document.getElementById('js-clock').textContent=timeString;//displays the time inside the html element

}
function formatTime(time)
{
    let hours=time.getHours();
    let ampm=hours>=12 ? 'pm':'am';  //finds if it is am or pm time

    hours=hours%12; //converts the hours to a 12 hrs format
    hours=hours ? hours:12; //converts 0 to 12

    let minutes=time.getMinutes();
    minutes=minutes<10 ? '0'+minutes:minutes; //adds the leading zero in case of single digit

    let seconds=time.getSeconds();
    seconds=seconds<10 ? '0'+seconds:seconds; //adds the leading zero in case of single digit

    return `${hours} : ${minutes} : ${seconds} ${ampm}`;
}
setInterval(getTime,1000); //updates the time every second
getTime(); //to initially display time
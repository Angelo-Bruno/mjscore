

function valor(){
    const arr = ["Insuficiente","bom","mto bom"];
    const nr = document.getElementById("valor");
    var text = document.getElementById("text");
    //parseInt(nr)
    
    if(nr>=0 && nr < 10){
        alert(arr[0])
        text.innerText = arr[0]
        console.log(nr)
       
    }
    else if(nr>=10 && nr < 14){
        text.innerText = arr[1]
        console.log(text.innerText)
    }
    else if(nr >= 14){
        text.innerText = arr[2]
        console.log(text.innerText)
    }
    

}

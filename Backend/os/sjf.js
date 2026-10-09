function sjfScheduling(processes){
  let comp=[];
  let rem=processes.slice();
  let time=0;
  while(rem.length>0){
    let shortest=-1;
    for(let i=0;i<rem.length;i++){
      if(rem[i].arrivalTime<=time){
        if(shortest==-1 || rem[i].burstTime<rem[shortest].burstTime){
          shortest=i;
        }
      }
    }
    if(shortest==-1){
      time++;
      continue;
    }
    let process=rem[shortest];
    process.state="Running";
    time+=process.burstTime;
    process.state="Completed";
    process.completionTime=time;
    process.turnaroundTime=process.completionTime-process.arrivalTime;
    process.waitingTime=process.turnaroundTime-process.burstTime;
    comp.push(process);
    rem.splice(shortest,1);
  }
  return comp;
}
module.exports={
  sjfScheduling:sjfScheduling
};
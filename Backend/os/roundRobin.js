function roundRobinScheduling(processes,tq){
  let queue=[];
  let comp=[];
  let time=0;
  let rem=processes.slice();
  while(rem.length>0 || queue.length>0){
    for(let i=0;i<rem.length;i++){
      if(rem[i].arrivalTime<=time){
        queue.push(rem[i]);
        rem.splice(i,1);
        i--;
      }
    }
    if(queue.length==0){
      time++;
      continue;
    }
    let process=queue.shift();
    process.state="Running";
    let runTime;
    if(process.remainingTime<tq){
      runTime=process.remainingTime;
    }else{
      runTime=tq;
    }
    time+=runTime;
    process.remainingTime=process.remainingTime-runTime;
    for(let i=0;i<rem.length;i++){
      if(rem[i].arrivalTime<=time){
        queue.push(rem[i]);
        rem.splice(i,1);
        i--;
      }
    }
    if(process.remainingTime==0){
      process.state="Completed";
      process.completionTime=time;
      process.turnaroundTime=process.completionTime-process.arrivalTime;
    process.waitingTime=process.turnaroundTime-process.burstTime;
    comp.push(process);
    }else{
      process.state="Ready";
      queue.push(process);
    }
  }
  return comp;
}
module.exports={
  roundRobinScheduling:roundRobinScheduling
};
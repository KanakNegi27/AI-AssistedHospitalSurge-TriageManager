
let resourceBusy=false;

let waitingQueue=Promise.resolve();

async function accessResource(allocationFunction){

  let releaseLock;

  let currentLock=new Promise(resolve=>{

    releaseLock=resolve;

  });

  let previousLock=waitingQueue;

  waitingQueue=waitingQueue.then(()=>currentLock);

  await previousLock;

  resourceBusy=true;

  try{

    return await allocationFunction();

  }finally{

    resourceBusy=false;

    releaseLock();

  }

}

module.exports={

  accessResource:accessResource

};
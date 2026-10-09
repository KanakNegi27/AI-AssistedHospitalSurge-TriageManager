let resourceBusy=false;
async function accessResource(allocationFunction) {
  while(resourceBusy){
    await new Promise(resolve=>setTimeout(resolve,100));
  }
  resourceBusy=true;
  try{
    return await allocationFunction();
  }finally{
    resourceBusy=false;
  }
}
module.exports={
  accessResource:accessResource
};
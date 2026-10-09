const {accessResource}=require("./synchronization");
async function criticalSection(allocationFunction) {
  return await accessResource(allocationFunction);
}
module.exports={
  criticalSection:criticalSection
};
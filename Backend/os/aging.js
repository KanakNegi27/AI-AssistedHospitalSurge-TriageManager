
function applyAging(processes, currentTime, waitingLimit) {
  if (!Number.isFinite(currentTime) || currentTime < 0) {
    throw new Error("currentTime must be non-negative");
  }

  if (!Number.isFinite(waitingLimit) || waitingLimit <= 0) {
    throw new Error("waitingLimit must be positive");
  }

  return processes.map(process => {
    const updated = { ...process };

    const isReady =
      updated.state === "Ready" ||
      updated.state === "NEW";

    const waitingTime = currentTime - updated.arrivalTime;

    if (
      isReady &&
      waitingTime >= waitingLimit &&
      updated.priority < 5
    ) {
      updated.priority = Math.min(
        5,
        updated.priority + 1
      );
      updated.lastAgingTime = currentTime;
    }

    return updated;
  });
}

module.exports = { applyAging };

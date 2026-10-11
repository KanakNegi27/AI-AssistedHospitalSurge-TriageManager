function detectStarvation(
  processes,
  currentTime,
  maxWaitingTime
) {
  if (!Number.isFinite(currentTime) || currentTime < 0) {
    throw new Error("currentTime must be non-negative");
  }

  if (
    !Number.isFinite(maxWaitingTime) ||
    maxWaitingTime <= 0
  ) {
    throw new Error("maxWaitingTime must be positive");
  }

  return processes
    .filter(process =>
      ["NEW", "Ready", "Waiting"].includes(process.state)
    )
    .map(process => ({
      ...process,
      waitingElapsed: Math.max(
        0,
        currentTime - process.arrivalTime
      ),
      starvationWarning:
        currentTime - process.arrivalTime >= maxWaitingTime
    }))
    .filter(process => process.starvationWarning);
}

module.exports = { detectStarvation };

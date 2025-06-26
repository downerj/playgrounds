/**
 * @param {(timestamp: DOMHighResTimeStamp) => void} callback
 * @param {number} interval
 */
export const setFramerateTimer = (callback, interval) => {
  let previous = 0;
  const onTick = timestamp => {
    if (timestamp - previous >= interval) {
      previous = timestamp;
      callback(timestamp);
    }
    window.requestAnimationFrame(onTick);
  };
  window.requestAnimationFrame(onTick);
};

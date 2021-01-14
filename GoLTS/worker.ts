import { parentPort, workerData } from 'worker_threads';
let tmp: number[] = [];

for (let j = 0; j < workerData.data[0].length; ++j) {
	let counter = 0;
	for (let k = workerData.id - 1; k < workerData.id + 2; ++k) {
		for (let l = j - 1; l < j + 2; ++l) {
			if (
				k >= 0 &&
				l >= 0 &&
				k < workerData.data.length &&
				l < workerData.data[0].length &&
				!(k == workerData.id && l == j)
			) {
				if (workerData.data[k][l] == 1) {
					++counter;
				}
			}
		}
	}
	if (workerData.data[workerData.id][j] && counter < 2) {
		tmp.push(0);
	} else if (workerData.data[workerData.id][j] && (counter == 2 || counter == 3)) {
		tmp.push(1);
	} else if (workerData.data[workerData.id][j] && counter > 3) {
		tmp.push(0);
	} else if (!workerData.data[workerData.id][j] && counter == 3) {
		tmp.push(1);
	} else {
		tmp.push(0);
	}
}
parentPort?.postMessage(tmp);

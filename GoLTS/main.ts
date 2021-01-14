import * as path from 'path';
import * as os from 'os';
import { Worker } from 'worker_threads';
import { resolve } from 'path';
import { constants } from 'os';

interface lineOfData {
	id: number;
	data: number[][];
}
async function paralelRound(args: lineOfData): Promise<number[]> {
	return new Promise((resolve, reject) => {
		const worker = new Worker(path.resolve(__dirname, './worker.js'), {
			workerData: args,
		});
		worker.on('message', (msg) => {
			resolve(msg);
		});

		worker.on('error', (err) => {
			reject(err);
		});
	});
}
function print(data: number[][]) {
	for (let i = 0; i < data.length; ++i) {
		for (let j = 0; j < data[i].length; ++j) {
			if (data[i][j] === 1) {
				process.stdout.write(' ■ '); //■
			} else {
				process.stdout.write('   ');
			}
		}
		console.log('|');
	}
}
function delay(ms: number) {
	return new Promise((resolve) => setTimeout(resolve, ms));
}

async function main() {
	// let playingBoard: number[][] = [
	// 	[1,1],
	// 	[1,0]];

	// let playingBoard: number[][] = [
	// 	[0, 0, 0, 0, 0, 0],
	// 	[0, 0, 0, 1, 0, 0],
	// 	[0, 1, 0, 0, 1, 0],
	// 	[0, 1, 0, 0, 1, 0],
	// 	[0, 0, 1, 0, 0, 0],
	// 	[0, 0, 0, 0, 0, 0],
	// ];

    let playingBoard: number[][] = [
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],

    ];

	print(playingBoard);
	while (true) {
		const jobs = [];
		for (let i = 0; i < playingBoard.length; i++) {
			jobs.push(paralelRound({ id: i, data: playingBoard }));
		}
		const result = await Promise.all(jobs);
		for (let i = 0; i < result.length; ++i) {
			playingBoard[i] = result[i];
		}
		console.clear();
		print(playingBoard);
		delay(250);
	}
}

main();

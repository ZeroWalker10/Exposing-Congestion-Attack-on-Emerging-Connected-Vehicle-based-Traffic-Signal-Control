import pandas as pd
import seaborn as sn
import matplotlib.pyplot as plt

result_files  = ['analysis.csv.34', 'analysis.csv']
result_titles = ['even distribution and sparse', 'not even distribution']
save_files = ['even_dist_sparse.png', 'not_even_dist.png']
for result, save in zip(result_files, save_files):
	df = pd.read_csv(result, header=None)
	sn.heatmap(df.values, linewidth=0.05, cmap='rainbow')
	plt.gca().invert_yaxis()
	plt.savefig(save, dpi=600)
	plt.xlabel('phase')
	plt.ylabel('arrival time')
	plt.show()

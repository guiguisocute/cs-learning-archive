import pandas as pd

def process_counter_log(filelogtest, out_csv="output.csv"):
    # 自动识别空格/tab 分隔
    df = pd.read_csv(filelogtest, delim_whitespace=True)
    
    # 导出 CSV
    df.to_csv(out_csv, index=False)
    print(f"已保存到 {out_csv}")
    return df

if __name__ == "__main__":
    df = process_counter_log("filelogtest")
    print(df.head())

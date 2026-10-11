from pathlib import Path
import pandas as pd

def load_dataset():
    path=Path()
    if not path.exists():
        raise FileNotFoundError(f"Dataset not found: {path}")
    df=pd.read_csv(path)
    df.columns=(
        df.columns.str.strip().str.lower().str.replace(" ","_",regex=False)
    )
    if df.empty:
        raise ValueError("The dataset is empty")
    return df

def clean_dataset(df):
    df=df.copy()
    df=df.drop_duplicates()
    if "date" in df.columns:
        df["date"]=pd.to_datetime(
            df["date"],
            dayfirst=True,
            errors="coerce"
        )
    for column in df.columns:
        if column not in ("date","hospital"):
            df[column]=pd.to_numeric(
                df[column],errors="coerce"
            )
    if "date" in df.columns:
        df=df.dropna(subset=["date"])
    return df.reset_index(drop=True)

def prepare_features(df,target_column):
    if target_column not in df.columns:
        raise ValueError(
            f"Target '{target_column}' not found."
            f"Available columns: {list(df.columns)}"
        )
    df=df.copy()
    future_columns=[
        column for column in df.columns
        if column.startswith("next_")
        or column.endswith("_shortage")
    ]
    X=df.drop(
        columns=[target_column]+future_columns,
        errors="ignore"
    )
    y=df[target_column]
    valid_rows=y.notna()
    X=X.loc[valid_rows].copy()
    y=y.loc[valid_rows].copy()
    if "date" in X.columns:
        X["day_of_week"] = X["date"].dt.dayofweek
        X["month"] = X["date"].dt.month
        X = X.drop(columns=["date"])
    if "hospital" in X.columns:
        X = pd.get_dummies(
            X, columns=["hospital"], dtype=int
        )
    X = X.replace([float("inf"), float("-inf")], float("nan"))
    return X,y

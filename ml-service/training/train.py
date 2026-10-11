from pathlib import Path
import sys
import joblib
import numpy as np
from sklearn.ensemble import RandomForestRegressor, RandomForestClassifier
from sklearn.impute import SimpleImputer
from sklearn.pipeline import Pipeline
from sklearn.metrics import (
    mean_absolute_error,
    mean_squared_error,
    accuracy_score,
    precision_score,
    recall_score,
    f1_score,
)

PROJECT_ROOT=Path(__file__).resolve().parents[2]
DATASET_PATH=PROJECT_ROOT/ "Sample-Dataset.csv"
MODEL_DIR=PROJECT_ROOT/"ml-service"/"models"

TARGET_COLUMNS=[
    "next_emergency",
    "next_critical",
    "icu_shortage",
    "vent_shortage"
]
def main():
    training_dir=Path(__file__).resolve().parent
    sys.path.insert(0,str(training_dir))
    from features import load_dataset,clean_dataset,prepare_features
    df=load_dataset()
    df=clean_dataset(df)
    print("Dataset columns:",df.columns.tolist())
    if "date" in df.columns:
        df=df.sort_values("date").reset_index(drop=True)
    targets=[
        column for column in TARGET_COLUMNS
        if column in df.columns
    ]
    if not targets:
        raise ValueError(
            "No target columns found. Expected"
            "'next_emergency' or 'next_critical'."
            f"Available columns: {df.columns.to_list()}"
        )
    MODEL_DIR.mkdir(parents=True,exist_ok=True)
    for target in targets:
        print(f"\nTraining model for: {target}")
        X,y=prepare_features(df,target)
        X=X.reset_index(drop=True)
        y=y.reset_index(drop=True)
        if len(X)<10:
            print(f"Skipping {target}: insufficient data")
            continue
        split_index=int(len(X)*0.8)
        X_train=X.iloc[:split_index]
        X_test=X.iloc[split_index:]
        y_train=y.iloc[:split_index]
        y_test=y.iloc[split_index:]
        if X_train.empty or X_test.empty:
            print(f"Skipping {target}: invalid data split")
            continue
        is_shortage=target in ("icu_shortage", "vent_shortage")
        if is_shortage:
            y_train=y_train.astype(int)
            y_test=y_test.astype(int)
            model=Pipeline([
                ("imputer", SimpleImputer(strategy="median")),
                ("classifier", RandomForestClassifier(
                    n_estimators=200,
                    random_state=42,
                    min_samples_leaf=2,
                    class_weight="balanced",
                    n_jobs=-1,
                )),
            ])
        else:
            model = Pipeline([
                ("imputer", SimpleImputer(strategy="median")),
                ("regressor", RandomForestRegressor(
                    n_estimators=200,
                    random_state=42,
                    min_samples_leaf=2,
                    n_jobs=-1,
                )),
            ])
        model.fit(X_train, y_train)
        predictions=model.predict(X_test)
        print(f"Training records: {len(X_train)}")
        print(f"Testing records: {len(X_test)}")
        if is_shortage:
            print("Model type: Classification")
            print(
                f"Accuracy:  "
                f"{accuracy_score(y_test, predictions):.3f}"
            )
            print(
                f"Precision: "
                f"{precision_score(y_test, predictions, zero_division=0):.3f}"
            )
            print(
                f"Recall: "
                f"{recall_score(y_test, predictions, zero_division=0):.3f}"
            )
            print(
                f"F1-score: "
                f"{f1_score(y_test, predictions, zero_division=0):.3f}"
            )
        else:
            print("Model type: Regression")
            mae = mean_absolute_error(y_test, predictions)
            rmse = np.sqrt(mean_squared_error(y_test, predictions))
            print(f"MAE:{mae:.2f}")
            print(f"RMSE:{rmse:.2f}")
        model_path = MODEL_DIR / f"{target}.joblib"
        joblib.dump(
            {
                "model": model,
                "features": X.columns.tolist(),
                "target": target,
            },
            model_path,
        )
        print(f"Model saved to: {model_path}")

if __name__=="__main__":
    main()
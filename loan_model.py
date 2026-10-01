# ===========================================
# Loan Approval ML + XAI
# ===========================================
import pandas as pd, shap, pickle
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier

cols = ['checking','duration','history','purpose','amount','savings','employment',
        'installment','personal','other','residence','property','age','other_plans',
        'housing','existing_credits','job','dependents','telephone','foreign','target']

df = pd.read_csv('german.data', sep=' ', names=cols)
df['file_row'] = df.index + 1
df = pd.get_dummies(df, drop_first=False)
X, y = df.drop('target', axis=1), df['target']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
model = RandomForestClassifier(n_estimators=100, random_state=42).fit(X_train, y_train)
print("Accuracy:", round(model.score(X_test, y_test) * 100, 2), "%")

explainer = shap.TreeExplainer(model)
sv = explainer.shap_values(X_test)
if isinstance(sv, list): sv = sv[1]
elif sv.ndim == 3: sv = sv[:, :, 1]

base_val = explainer.expected_value
if isinstance(base_val, (list, tuple)): base_val = base_val[1]
elif hasattr(base_val, '__len__') and len(base_val) > 1: base_val = base_val[1]

print("\nGenerating SHAP graphs...")
shap.summary_plot(sv, X_test, plot_type="bar", show=False)
plt.tight_layout(); plt.savefig('shap_global.png', dpi=150); plt.close()
shap.summary_plot(sv, X_test, show=False)
plt.tight_layout(); plt.savefig('shap_beeswarm.png', dpi=150); plt.close()
shap.waterfall_plot(shap.Explanation(values=sv[0], base_values=base_val,
    data=X_test.iloc[0], feature_names=X_test.columns.tolist()), show=False)
plt.tight_layout(); plt.savefig('shap_applicant0.png', dpi=150); plt.close()
print("Saved: shap_global.png, shap_beeswarm.png, shap_applicant0.png")

print("\n===== WORD EXPLANATIONS =====")
for i in range(10):
    row = X_test.iloc[i]
    pred = model.predict(X_test.iloc[[i]])[0]
    decision = "APPROVED" if pred == 1 else "DENIED"
    score = base_val + sv[i].sum()

    fails = []
    if row.get('checking_A11', 0) == 1: fails.append("Checking Account")
    if row.get('duration', 0) > 24: fails.append("Loan Duration > 24m")
    if row.get('history_A33', 0) == 1 or row.get('history_A34', 0) == 1: fails.append("Credit History")
    if row.get('amount', 0) >= 7500: fails.append("Amount >= 7500")
    if row.get('savings_A65', 0) == 1: fails.append("Low Savings")
    if row.get('employment_A71', 0) == 1 or row.get('employment_A72', 0) == 1: fails.append("Unemployed")

    contrib = pd.Series(sv[i], index=X_test.columns)
    top3 = contrib.abs().sort_values(ascending=False).head(3).index

    print(f"\nApplicant {int(row.get('file_row', 0))}: ML says {decision} | Rules say {'DENIED' if fails else 'APPROVED'}")
    print(f"  Prediction score: {score:.3f}")
    print(f"  Top 3 features:")
    for f in top3:
        print(f"    - {f} (impact: {contrib[f]:+.3f}) -> {'toward approval' if contrib[f] > 0 else 'toward denial'}")

with open('loan_model.pkl', 'wb') as f:
    pickle.dump(model, f)
print("\nModel saved as loan_model.pkl")
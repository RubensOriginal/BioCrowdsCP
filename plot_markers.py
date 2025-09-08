import pandas as pd
import plotly.graph_objects as go

# Carrega os arquivos CSV
df_markers = pd.read_csv("./output/markers.csv")
df_cells = pd.read_csv("./output/cells.csv")

fig = go.Figure()

# Adiciona as células como quadrados atrás dos markers
for _, row in df_cells.iterrows():
    fig.add_shape(
        type="rect",
        x0=row["cell_x"], y0=row["cell_z"],
        x1=row["cell_x"] + 2,  # largura da célula (ajuste se necessário)
        y1=row["cell_z"] + 2,  # altura da célula (ajuste se necessário)
        line=dict(color="LightGray", width=1),
        fillcolor="LightGray",
        layer="below"  # coloca as células atrás dos markers
    )

# Adiciona os markers como pontos, sempre na frente
fig.add_trace(go.Scatter(
    x=df_markers["x"],
    y=df_markers["y"],
    mode="markers",
    marker=dict(size=6, color="blue"),
    text=[f"Cell=({cx},{cy}) Marker={mid}"
          for cx, cy, mid in zip(df_markers["cell_x"],
                                 df_markers["cell_y"],
                                 df_markers["marker_id"])],
    hoverinfo="text"
))

fig.update_layout(
    title="World Grid com Markers",
    xaxis=dict(scaleanchor="y", title="X"),
    yaxis=dict(title="Y"),
    width=600,
    height=600
)

fig.show()

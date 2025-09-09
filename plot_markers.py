import pandas as pd
import plotly.graph_objects as go

# Lê os arquivos
df_markers = pd.read_csv("./output/markers.csv")  # marker_x, marker_z
df_cells = pd.read_csv("./output/cells.csv")      # cell_x, cell_z

CELL_SIZE = 2  # cada célula é 2x2

# Cria a figura base
fig = go.Figure()

# Adiciona os pontos (markers)
fig.add_trace(go.Scatter(
    x=df_markers["marker_x"],
    y=df_markers["marker_z"],
    mode="markers",
    marker=dict(size=4, color="red"),
    name="Markers"
))

# Adiciona as células como retângulos
for _, row in df_cells.iterrows():
    x0, z0 = row["cell_x"] * CELL_SIZE, row["cell_z"] * CELL_SIZE
    x1, z1 = x0 + CELL_SIZE, z0 + CELL_SIZE

    fig.add_shape(
        type="rect",
        x0=x0, y0=z0,
        x1=x1, y1=z1,
        line=dict(color="blue", width=1),
        fillcolor="rgba(0,0,255,0.1)"  # azul transparente
    )

# Configuração do layout
fig.update_layout(
    title="Markers e Células 2x2 (escaladas)",
    xaxis_title="X",
    yaxis_title="Z",
    xaxis=dict(scaleanchor="y", scaleratio=1),  # mantém proporção
    showlegend=True
)

fig.show()

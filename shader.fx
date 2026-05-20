/*

Kode ini dibuat untuk mengendalikan shader pada tutorial sebelumnya, namun saat ini
fungsinya sudah dialihkan menjadi file terpisah yaitu VertexShader.hlsl dan PixelShader.hlsl,
sehingga kode ini tidak digunakan lagi dan hanya sebagai pembelajaran saja.

float4 vsmain(float4 pos : POSITION) : SV_POSITION
{
    return pos;
}

float4 psmain(float4 pos : SV_POSITION) : SV_Target
{
    return float4(0.7f, 0.9f,0.8f, 1.0f); // Modifikasi warna object render sesuai kebutuhan
}
*/
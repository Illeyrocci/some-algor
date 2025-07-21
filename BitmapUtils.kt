package ru.rutube.uikit.utils

import android.graphics.Bitmap
import androidx.core.graphics.get
import androidx.core.graphics.set
import kotlin.math.sqrt
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.withContext

/**
 * Асинхронно перекрашивает [Bitmap], заменяя цвета на ближайшие из [colorMap] с учётом
 * допустимого цветового расстояния [tolerance].
 *
 * @param colorMap Сопоставление исходных цветов (ключ) и цветов-замен (значение) в формате ARGB Int.
 * @param tolerance Максимально допустимое расстояние в цветовом пространстве RGB для замены цвета.
 *                  Значение задаёт порог похожести цвета и необходимо для сглаживания при перерисовке.
 *                  Допустимые значения — от 0 (только точное совпадение) до ≈440.
 */
suspend fun Bitmap.recolor(colorMap: Map<Int, Int>, tolerance: Float = 50f) = withContext(Dispatchers.Default) {
    for (x in 0 until width) {
        for (y in 0 until height) {
            val pixel = get(x, y)
            if (pixel ushr 24 == 0) {
                continue
            }
            val replacement = colorMap[
                findClosestColor(
                    original = pixel,
                    colors = colorMap.keys,
                    maxDistance = tolerance,
                ),
            ]
            set(x = x, y = y, color = replacement ?: pixel)
        }
    }
}

private fun findClosestColor(original: Int, colors: Set<Int>, maxDistance: Float): Int {
    val r = (original shr 16) and 0xFF
    val g = (original shr 8) and 0xFF
    val b = original and 0xFF

    var closestColor = original
    var minDistance = maxDistance

    for (color in colors) {
        val kr = (color shr 16) and 0xFF
        val kg = (color shr 8) and 0xFF
        val kb = color and 0xFF

        val distance = sqrt(
            ((r - kr) * (r - kr) + (g - kg) * (g - kg) + (b - kb) * (b - kb)).toFloat(),
        )

        if (distance < minDistance) {
            minDistance = distance
            closestColor = color
        }
    }
    return closestColor
}

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
	<xsl:template match="/">
		<html>
			<body>
			<h2>Schedule</h2>
				<table border="1">
					<tr bgcolor="#918380">
					<th style="text-align:left">Title</th>
					<th style="text-align:left">Professor</th>
					<th style="text-align:left">Day</th>
					</tr>
						<xsl:for-each select="//Lesson[Lecture/Day = 'Monday']">
							<tr bgcolor="#CD202A">
								<td><xsl:value-of select="Title"/></td>
								<td><xsl:value-of select="Professor"/></td>
								<td>Monday</td>
							</tr>
						</xsl:for-each>
						<xsl:for-each select="//Lesson[Lecture/Day = 'Tuesday']">
							<tr bgcolor="#42CD20">
								<td><xsl:value-of select="Title"/></td>
								<td><xsl:value-of select="Professor"/></td>
								<td>Tuesday</td>
							</tr>
						</xsl:for-each>
						<xsl:for-each select="//Lesson[Lecture/Day = 'Wednesday']">
							<tr bgcolor="#0B5EE5">
								<td><xsl:value-of select="Title"/></td>
								<td><xsl:value-of select="Professor"/></td>
								<td>Wednesday</td>
							</tr>
						</xsl:for-each>
						<xsl:for-each select="//Lesson[Lecture/Day = 'Thursday']">
							<tr bgcolor="#E1DE0F">
								<td><xsl:value-of select="Title"/></td>
								<td><xsl:value-of select="Professor"/></td>
								<td>Thursday</td>
							</tr>
						</xsl:for-each>
						<xsl:for-each select="//Lesson[Lecture/Day = 'Friday']">
							<tr bgcolor="#B40FE1">
								<td><xsl:value-of select="Title"/></td>
								<td><xsl:value-of select="Professor"/></td>
								<td>Friday</td>
							</tr>
						</xsl:for-each>
						<xsl:for-each select="//Lesson[Lecture/Day = 'Saturday']">
							<tr bgcolor="#E5920B">
								<td><xsl:value-of select="Title"/></td>
								<td><xsl:value-of select="Professor"/></td>
								<td>Saturday</td>
							</tr>
						</xsl:for-each>
						<xsl:for-each select="//Lesson[Lecture/Day = 'Sunday']">
							<tr bgcolor="#38853A">
								<td><xsl:value-of select="Title"/></td>
								<td><xsl:value-of select="Professor"/></td>
								<td>Sunday</td>
							</tr>
						</xsl:for-each>
				</table>
			</body>
		</html>
	</xsl:template>
</xsl:stylesheet>
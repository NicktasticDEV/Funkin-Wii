<div align='center'><img src="https://upload.wikimedia.org/wikipedia/commons/thumb/d/d2/Friday_Night_Funkin%27_logo.svg/2560px-Friday_Night_Funkin%27_logo.svg.png" width="200">
<h3>Wii Port</h3>
</div>

<h1> Welcome! </h1>
<p>This is a rewrite of <a href="https://github.com/FunkinCrew/Funkin">Friday Night Funkin'</a> made to run on the Nintendo Wii!</p>

<h1>How to compile</h1>

<h3><p>The Docker way (Recommended)</p></h3>
<p>To compile the project using Docker, you can use the provided Dockerfile.wii to build a Docker image with all the necessary dependencies.</p>
<pre>
docker build -f docker/Dockerfile.wii --target exporter -o . .
</pre>

<hr>

<h3><p>The Manual Way</p></h3>
<p>Make sure you have <a href="https://www.devkitpro.org/">devkitPro</a> installed.</p>

<p>You will need to install the following libraries</p>
<ul>
    <li><a href="https://github.com/GRRLIB/GRRLIB">GRRLIB</a></li>
    <li><a href="https://github.com/leethomason/tinyxml2">Tinyxml2</a></li>
    <li><a href="https://github.com/NateXS/libromfs-ogc">libromfs-ogc</a></li>
</ul>

<p> To install Tinyxml2, you can use the following command:</p>
<pre>
sudo dkp-pacman -S ppc-tinyxml2     
</pre>
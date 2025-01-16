





// Wait for window to load
window.onload = function() {
    // Select the loader container
    const loaderContainer = document.querySelector('.loader-container');
    
    // Hide loader after 2 seconds
    setTimeout(function() {
      loaderContainer.style.display = 'none';
      // Remove the hidden-until-loaded class to show the main content
      document.querySelector('.hidden-until-loaded').classList.remove('hidden-until-loaded');
    }, 2000); // 2000 milliseconds = 2 seconds
  };
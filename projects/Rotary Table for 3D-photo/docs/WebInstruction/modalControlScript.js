function showModal(elem) {
	elem.nextElementSibling.style.display = 'block';
	elem.nextElementSibling.children[1].src = elem.src;
	elem.nextElementSibling.children[2].innerHTML = elem.alt;
}

// When the user clicks on <span> (x), close the modal
function closeModal(elem) {
  elem.parentElement.style.display = 'none';
} 

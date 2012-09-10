<div class="view">

	<b><?php echo CHtml::encode($data->getAttributeLabel('id')); ?>:</b>
	<?php echo CHtml::link(CHtml::encode($data->id), array('view', 'id'=>$data->id)); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('first_name')); ?>:</b>
	<?php echo CHtml::encode($data->first_name); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('last_name')); ?>:</b>
	<?php echo CHtml::encode($data->last_name); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('sex')); ?>:</b>
	<?php echo CHtml::encode($data->sex); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('photo')); ?>:</b>
	<?php echo CHtml::encode($data->photo); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('date_of_birth')); ?>:</b>
	<?php echo CHtml::encode($data->date_of_birth); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('ethnic_group')); ?>:</b>
	<?php echo CHtml::encode($data->ethnic_group); ?>
	<br />

	<?php /*
	<b><?php echo CHtml::encode($data->getAttributeLabel('political_status')); ?>:</b>
	<?php echo CHtml::encode($data->political_status); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('birth_place_city')); ?>:</b>
	<?php echo CHtml::encode($data->birth_place_city); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('birth_place_province')); ?>:</b>
	<?php echo CHtml::encode($data->birth_place_province); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('original_residence_city')); ?>:</b>
	<?php echo CHtml::encode($data->original_residence_city); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('original_residence_province')); ?>:</b>
	<?php echo CHtml::encode($data->original_residence_province); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('home_address')); ?>:</b>
	<?php echo CHtml::encode($data->home_address); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('home_postcode')); ?>:</b>
	<?php echo CHtml::encode($data->home_postcode); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('home_phone')); ?>:</b>
	<?php echo CHtml::encode($data->home_phone); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('email')); ?>:</b>
	<?php echo CHtml::encode($data->email); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('phone')); ?>:</b>
	<?php echo CHtml::encode($data->phone); ?>
	<br />

	<b><?php echo CHtml::encode($data->getAttributeLabel('identity_card_number')); ?>:</b>
	<?php echo CHtml::encode($data->identity_card_number); ?>
	<br />

	*/ ?>

</div>